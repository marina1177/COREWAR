import code
from typing import List
import arcade
import timeit
import argparse
import sys
import codecs
import os
import json
from pprint import pprint
import math
from pathlib import Path
from typing import Union
import ffmpeg
import pygame


MEM_SIZE = (4*1024)
SQUARE_SPACING = 12

SCREEN_WIDTH = int(math.sqrt(MEM_SIZE) * SQUARE_SPACING) + 20
SCREEN_HEIGHT = int(math.sqrt(MEM_SIZE) * SQUARE_SPACING) + 20
SCREEN_TITLE = "Arena"

HALF_SQUARE = int((SQUARE_SPACING - 2) / 2) if SQUARE_SPACING % 2 == 0 else int((SQUARE_SPACING - 1) / 2)


CARR_BORD_W = SQUARE_SPACING - 2*(HALF_SQUARE)
CARR_WIDTH = 2 * HALF_SQUARE
CARR_HEIGHT = 2 * HALF_SQUARE

COLOR_PLAYER = [arcade.color.RED, arcade.color.AMBER, arcade.color.APPLE_GREEN, arcade.color.BLUEBERRY]
COLOR_WRITE = [arcade.color.ALABAMA_CRIMSON, arcade.color.LEMON_GLACIER, arcade.color.GREEN, arcade.color.AQUA]
OP_CODE = ['lv', 'd', 'st', 'ad', 'su', '&', 'or', 'xo', 'zj', 'di', 'si', 'fk', 'll', 'li', 'lf', 'af']

class Consts(object):
	def __init__(self, mem_size = 4096, cycle_delta = 50, players_number = 0,
	             max_checks = 10, const_nbr_live = 21, const_cycle_to_die = 1536):
		self.mem_size = mem_size
		self.sq_spacing = 10
		self.screen = (self.mem_size / self.sq_spacing) + 20
		self.half_sq = ((self.sq_spacing - 2) / 2 if self.sq_spacing % 2 == 0 else self.sq_spacing / 2)

		self.cycle_delta = cycle_delta
		self.players_number = players_number
		self.max_checks = max_checks
		self.const_nbr_live = const_nbr_live
		self.const_cycle_to_die = const_cycle_to_die


class State(object):
	def __init__(self, total_process = -1, cycle_to_die = -1, nbr_live = -1):
		self.total_process = total_process
		self.cycle_to_die = cycle_to_die
		self.nbr_live = nbr_live

class Champion(object):
	def __init__(self, id = -1, name=None, start_code = 0, size_code=0):
		self.id = id
		self.name = name
		self.start_code = start_code
		self.size_code = size_code
		self.area = size_code
		self.is_alive = 1
		self.last_live = 0
		self.lives_in_period = 0

class Carriages(object):
	def __init__(self, id=-1, op_code=0, place=0):
		self.id = id
		self.op_code = op_code
		self.place = place
		self.x_cntr = -1
		self.y_cntr = -1

class MyGame(arcade.Window):

	def __init__(self, width, height, title, data, const, state):
		super().__init__(width, height, title)
		arcade.set_background_color(arcade.color.BLACK)
		self.data = data

		self.cycle = 0
		self.speed = -10
		self.json_indx = 0
		self.frame_count = 0
		self.draw_time = 0

		self.shape_list = None
		self.point_list = []
		self.color_list = []

		self.const = const
		self.state = state

		self.players = []
		self.carriage_list = []

		self.game_over = False

		for i in range(len(self.data[0]['Consts']['Players'])):
			player = Champion(self.data[0]['Consts']['Players'][i]['id'],
			                  self.data[0]['Consts']['Players'][i]['name'],
			                  self.data[0]['Consts']['Players'][i]['start_code'],
			                  self.data[0]['Consts']['Players'][i]['exec_code_size'])
			self.players.append(player)

		for i in range(len(self.data[0]['Carriages'])):
			carr = Carriages(self.data[0]['Carriages'][i]['id'],
			                 self.data[0]['Carriages'][i]['op_code'],
			                 self.data[0]['Carriages'][i]['place'])
			self.carriage_list.append(carr)

	def setup(self):

		self.shape_list = arcade.ShapeElementList()

		cnt = 0
		for y in range(SCREEN_WIDTH - 10 - HALF_SQUARE, 10, -SQUARE_SPACING):
			for x in range(HALF_SQUARE + 10, SCREEN_WIDTH-10, SQUARE_SPACING):

				top_left = (x - HALF_SQUARE, y + HALF_SQUARE)
				top_right = (x + HALF_SQUARE, y + HALF_SQUARE)
				bottom_right = (x + HALF_SQUARE, y - HALF_SQUARE)
				bottom_left = (x - HALF_SQUARE, y - HALF_SQUARE)

				self.point_list.append(top_left)
				self.point_list.append(top_right)
				self.point_list.append(bottom_right)
				self.point_list.append(bottom_left)

				for k in range(0, len(self.players)):
					n = self.players[k].size_code + self.players[k].start_code
					if(cnt < n) & (cnt >= self.players[k].start_code):
						for i in range(4):
							self.color_list.append((COLOR_PLAYER[self.players[k].id - 1]))
						break
					else:
						if k == len(self.players) - 1:
							for i in range(4):
								self.color_list.append(arcade.color.BATTLESHIP_GREY)
						else:
							continue
				cnt = cnt + 1
		shape = arcade.create_rectangles_filled_with_colors(self.point_list, self.color_list)
		self.shape_list.append(shape)


	def state_refresh(self, data_state):
		#print('state_refresh')
		self.state = State(data_state['total_process'], data_state['cycle_to_die'],  data_state['nbr_live'])


	def players_refresh(self, data_pl):
		#print('players_refresh')
		for i in range(0, len(self.players)):
			self.players[i].is_alive = data_pl[i]['is_alive']
			self.players[i].last_live = data_pl[i]['last_live']
			self.players[i].lives_in_period = data_pl[i]['lives_in_period']

	def carr_refresh(self, data_carr, point_list):
		#print('carr_refresh')
		del self.carriage_list[:]

		for i in range(0, len(data_carr)):
			bl0, bl1 = point_list[data_carr[i]['place'] * 4 + 3]
			carr = Carriages(data_carr[i]['id'],
			                 data_carr[i]['op_code'],
			                 data_carr[i]['place'])
			carr.x_cntr = bl0
			carr.y_cntr = bl1
			#print('carr.x=', carr.x_cntr, 'carr.y =', carr.y_cntr)
			self.carriage_list.append(carr)

	def cell_refresh(self, data_cell):
		#print('cell_refresh')
		for i in range(0, len(data_cell)):
			for j in range(0, len(data_cell[i]['cells_address'])):
				#print(data_cell[i]['cells_address'][j])

				start_place = data_cell[i]['cells_address'][j] * 4
			# меняю счетчик занятой игроком площади
				for k in range(0, len(self.players)):
					if self.color_list[start_place] == COLOR_PLAYER[data_cell[i]['id'] - 1]:
						print('color', self.color_list[start_place], 'is', data_cell[i]['id'], 'player')
						break
					elif (self.color_list[start_place] == COLOR_PLAYER[self.players[k].id - 1]):
						self.players[k].area -= 1
						self.players[len(self.players) - data_cell[i]['id']].area += 1
						break
					elif self.color_list[start_place] == arcade.color.BATTLESHIP_GREY:
						self.players[len(self.players) - data_cell[i]['id']].area += 1
						break
			# меняю цвет ячейки
				for n in range(0, 4):
					self.color_list[start_place + n] = COLOR_WRITE[data_cell[i]['id'] - 1]
					print(str(self.color_list[start_place + n]))

	def drop(self):
		"""del self.shape_list[:]
		self.shape_list = arcade.ShapeElementList()"""

		# State refresh
		if self.data[self.json_indx]['state_refresh'] > 0:
			if self.data[self.json_indx]['State']['error_code'] > 0:
				self.game_over = True
			else:
				self.state_refresh(self.data[self.json_indx]['State'])
		# Players refresh
		if self.data[self.json_indx]['players_refresh'] > 0:
			self.players_refresh(self.data[self.json_indx]['Players'])
		# Carriages refresh
		if self.data[self.json_indx]['carriage_refresh'] > 0:
			self.carr_refresh(self.data[self.json_indx]['Carriages'], self.point_list)
		# Cell color refresh
		if self.data[self.json_indx]['cells_refresh'] > 0:
			self.cell_refresh(self.data[self.json_indx]['Cells'])
		self.cycle = self.data[self.json_indx]['cycle']

		shape = arcade.create_rectangles_filled_with_colors(self.point_list, self.color_list)
		self.shape_list.append(shape)

	def draw_info(self):
		start_y = SCREEN_WIDTH - 20
		start_x = SCREEN_WIDTH + 20
		# arcade.draw_point(start_x, start_y, arcade.color.BLUE, 5)
		if self.game_over == False:
			arcade.draw_text("game state: **running**",
		                 start_x, start_y, arcade.color.WHITE, 12)
		start_y -= 20
		output = f"Drawing time: {self.draw_time:.5f} seconds per frame."
		arcade.draw_text(output, start_x, start_y, arcade.color.WHITE, 12)


		start_y -= 40
		mystr = 'total process: ' + str(self.state.total_process)
		arcade.draw_text(mystr, start_x, start_y, arcade.color.WHITE, 12)
		start_y -= 20
		mystr = 'cycle: ' + str(self.cycle)
		arcade.draw_text(mystr, start_x, start_y, arcade.color.WHITE, 12)

		start_y -= 40
		mystr = 'cycle to die: ' + str(self.state.cycle_to_die)
		arcade.draw_text(mystr, start_x, start_y, arcade.color.WHITE, 12)
		start_y -= 20
		mystr = 'cycle delta: ' + str(self.const.cycle_delta)
		arcade.draw_text(mystr, start_x, start_y, arcade.color.WHITE, 12)

		start_y -= 40
		mystr = 'nbr_live: ' + str(self.state.nbr_live) + '/' + str(self.const.const_nbr_live)
		arcade.draw_text(mystr, start_x, start_y, arcade.color.WHITE, 12)
		"""start_y -= 20
		mystr = 'max_checks: ' + str(self.state.max_checks) + '/' + str(self.const.const_max_checks)
		arcade.draw_text(mystr, start_x, start_y, arcade.color.WHITE, 12)"""
		start_y -= 50
		for i in range(0, len(self.players)):

			mystr = 'player: ' + str(self.players[i].id)
			arcade.draw_text(mystr, start_x, start_y, arcade.color.WHITE, 12)

			start_y -= 20
			arcade.draw_text(self.players[i].name, start_x, start_y, COLOR_WRITE[self.players[i].id - 1], 12)

			start_y -= 20
			mystr = 'last live: ' + str(self.players[i].last_live)
			arcade.draw_text(mystr, start_x, start_y, arcade.color.WHITE, 12)

			start_y -= 20
			mystr = 'lives in current period: ' + str(self.players[i].lives_in_period)
			arcade.draw_text(mystr, start_x, start_y, arcade.color.WHITE, 12)

			"""start_y -= 20
			mystr = 'area = ' + str(self.players[i].area)
			arcade.draw_text(mystr, start_x, start_y, arcade.color.WHITE, 12)"""

			start_y -= 30
		#print('star_x =', start_x, 'start_y =', start_y)


	def draw_carr(self, carr_list):
		#print('Draw carr')
		for i in range(0, len(carr_list)):
			bl0, bl1 = self.point_list[self.carriage_list[i].place * 4 + 3]
			carr_list[i].x_cntr = bl0 + HALF_SQUARE
			carr_list[i].y_cntr = bl1 + HALF_SQUARE

			arcade.draw_rectangle_outline(carr_list[i].x_cntr, carr_list[i].y_cntr,
			                              CARR_WIDTH, CARR_HEIGHT,
			                              arcade.color.WHITE, CARR_BORD_W, 0)
			arcade.draw_text(OP_CODE[carr_list[i].op_code], bl0, bl1, arcade.color.BLACK, 8)


	def draw_schem(self):
		# print('Draw schem')
		start_x = start_x = SCREEN_WIDTH + 20
		start_y = 120

		arcade.draw_text('arena distribution:', start_x, start_y, arcade.color.WHITE, 12)
		start_y -= 10
		arcade.draw_lrtb_rectangle_outline(start_x, start_x + MEM_SIZE/10 + 2, start_y, start_y - 12,
		                             arcade.color.WHITE, 2)
		start_x += 2
		start_y -= 2
		sum_area = 0
		for i in range(0, len(self.players)):
			sum_area += self.players[i].area
			arcade.draw_lrtb_rectangle_filled(start_x, start_x + self.players[i].area/10,
			                                  start_y, start_y - 8,
			                                  COLOR_WRITE[self.players[i].id - 1])
			start_x += self.players[i].area/10

		arcade.draw_lrtb_rectangle_filled(start_x, start_x + (self.const.mem_size - sum_area)/10,
		                                  start_y, start_y - 8,
		                                  arcade.color.BATTLESHIP_GREY)


	def on_draw(self):
		#print('>>on_draw>>')

		arcade.start_render()
		draw_start_time = timeit.default_timer()
		self.shape_list.draw()
		self.draw_carr(self.carriage_list)
		self.draw_info()
		self.draw_schem()
		self.draw_time = timeit.default_timer() - draw_start_time

	def update(self, delta_time):
		#print('update')
		"""self.frame_count += 1
		if self.frame_count % 10 == 0:
			self.json_indx += 1
			if self.json_indx < len(self.data):
				self.drop()"""

		if self.speed > 0:
			self.json_indx += self.speed if self.json_indx != 0 else 1
			if self.json_indx <= len(self.data) - 1:
				self.drop()
			else:
				self.game_over = True
		if self.speed < 0:
			self.frame_count += 1 # обнулить в key_press
		if self.frame_count % int(math.fabs(self.speed)) == 0:
			self.json_indx += 1
			if self.json_indx < len(self.data):
				self.drop()
			elif self.json_indx > len(self.data) - 1:
				self.json_indx = len(self.data) - 1
				self.drop()
				self.game_over = True

	def on_key_press(self, key, modifiers):

		if key == arcade.key.UP:
			self.frame_count = 0
			dt = (2 if self.speed == -1 else 1)
			self.speed += dt
			if self.speed > 10:
				self.speed = 10
		elif key == arcade.key.DOWN:
			self.frame_count = 0
			self.speed -= (2 if self.speed == 1 else 1)
			if self.speed < -10:
				self.speed = -10
		print('speed =', self.speed)

def main():
	pygame.init()
	pygame.mixer.music.load('sound/Secret_of_Mana_Desert_Snowstorm_OC_ReMix.mp3')
	pygame.mixer.music.play(- 1)
	with open('vis.json') as f:
		data = json.load(f)
	const = Consts(data[0]['Consts']['mem_size'],
		               data[0]['Consts']['cycle_delta'],
		               data[0]['Consts']['players_number'],
		               data[0]['Consts']['max_checks'],
		               data[0]['Consts']['const_nbr_live'],
		               data[0]['Consts']['const_cycle_to_die'])

	const.sq_spacing = 12

	if ('State' in data[0]) & (data[0]['State']['error_code'] == 0):
		state = State(data[0]['State']['total_process'],
		               data[0]['State']['cycle_to_die'],
		               data[0]['State']['nbr_live'])

		MEM_SIZE = const.mem_size
		const.sq_spacing = SQUARE_SPACING
		window = MyGame(SCREEN_WIDTH + 500, SCREEN_HEIGHT, 'Arena',
			                data, const, state)
		window.setup()
		arcade.run()


if __name__ == "__main__":
	main()