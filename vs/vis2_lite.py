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

MEM_SIZE = (4*1024)
SCREEN_WIDTH = 640 + 20
SCREEN_HEIGHT = 640 + 20
SCREEN_TITLE = "Arena"

HALF_SQUARE_WIDTH = 4
HALF_SQUARE = 4
SQUARE_SPACING = 10

CARR_BORD_W = SQUARE_SPACING - 2*(HALF_SQUARE)
CARR_WIDTH = 2 * HALF_SQUARE
CARR_HEIGHT = 2 * HALF_SQUARE

COLOR_PLAYER = [arcade.color.RED, arcade.color.GOLD, arcade.color.GREEN, arcade.color.BLUEBERRY]
COLOR_WRITE = [arcade.color.ALABAMA_CRIMSON, arcade.color.LEMON_GLACIER, arcade.color.LINCOLN_GREEN, arcade.color.AQUA]


class Consts(object):
	def __init__(self, mem_size = 4096, cycle_delta = 50, players_number = 0,
	             max_checks = 10, const_nbr_live = 21, const_cycle_to_die = 1536):
		self.mem_size = mem_size
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

				top_left = (x - HALF_SQUARE_WIDTH, y + HALF_SQUARE)
				top_right = (x + HALF_SQUARE_WIDTH, y + HALF_SQUARE)
				bottom_right = (x + HALF_SQUARE_WIDTH, y - HALF_SQUARE)
				bottom_left = (x - HALF_SQUARE_WIDTH, y - HALF_SQUARE)

				self.point_list.append(top_left)
				self.point_list.append(top_right)
				self.point_list.append(bottom_right)
				self.point_list.append(bottom_left)

				for k in range(0, len(self.players)):
					n = self.players[k].size_code + self.players[k].start_code
					if(cnt < n) & (cnt >= self.players[k].start_code):
						for i in range(4):
							self.color_list.append((COLOR_PLAYER[self.players[k].id]))
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
		#print('total_process:', data_state['total_process'],'\ncycle_to_die:', data_state['cycle_to_die'] )
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
			print('carr.x=', carr.x_cntr, 'carr.y =', carr.y_cntr)
			self.carriage_list.append(carr)

	def cell_refresh(self, data_cell):
		#print('cell_refresh')
		for i in range(0, len(data_cell)):
			start_place = data_cell[i]['cell_address'] * 4
			for k in range(0, 4):
				self.color_list[start_place + k] = COLOR_WRITE[data_cell[i]['player_id'] - 1]


	def drop(self):
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
			self.cell_refresh(self.data[self.json_indx]['Cells'], self.color_list)
		self.cycle = self.data[self.json_indx]['cycle']

	def draw_info(self):
		start_y = SCREEN_WIDTH - 20
		start_x = SCREEN_WIDTH + 20
		# arcade.draw_point(start_x, start_y, arcade.color.BLUE, 5)
		if self.game_over == False:
			arcade.draw_text("game over: **running**",
		                 start_x, start_y, arcade.color.WHITE, 12)
		start_y -= 40
		mystr = 'total process: ' + str(self.state.total_process)
		arcade.draw_text(mystr, start_x, start_y, arcade.color.WHITE, 12)
		start_y -= 20
		mystr = 'cycle: ' + str(self.cycle)
		arcade.draw_text(mystr, start_x, start_y, arcade.color.WHITE, 12)

		start_y -= 40
		mystr = 'cycle to die: ' + str(self.const.const_cycle_to_die)
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
			arcade.draw_text(self.players[i].name, start_x, start_y, COLOR_PLAYER[self.players[i].id], 12)

			start_y -= 20
			mystr = 'last live: ' + str(self.players[i].last_live)
			arcade.draw_text(mystr, start_x, start_y, arcade.color.WHITE, 12)

			start_y -= 20
			mystr = 'lives in current period: ' + str(self.players[i].lives_in_period)
			arcade.draw_text(mystr, start_x, start_y, arcade.color.WHITE, 12)

			start_y -= 30


	def draw_carr(self, carr_list):
		#print('Draw carr')
		for i in range(0, len(carr_list)):
			bl0, bl1 = self.point_list[self.carriage_list[i].place * 4 + 3]
			carr_list[i].x_cntr = bl0 + HALF_SQUARE
			carr_list[i].y_cntr = bl1 + HALF_SQUARE

			arcade.draw_rectangle_outline(carr_list[i].x_cntr, carr_list[i].y_cntr,
			                              CARR_WIDTH, CARR_HEIGHT,
			                              arcade.color.WHITE, CARR_BORD_W, 0)

	def on_draw(self):
		#print('>>on_draw>>')

		arcade.start_render()
		draw_start_time = timeit.default_timer()
		self.shape_list.draw()
		self.draw_carr(self.carriage_list)
		self.draw_info()

		output = f"Drawing time: {self.draw_time:.5f} seconds per frame."
		arcade.draw_text(output, 20, SCREEN_HEIGHT - 40, arcade.color.WHITE, 18)

		self.draw_time = timeit.default_timer() - draw_start_time

	def update(self, delta_time):
		#print('update')
		self.frame_count += 1
		if self.frame_count % 10 == 0:
			self.json_indx += 1
			if self.json_indx < len(self.data):
				self.drop()

def main():
	with open('vis.json') as f:
		data = json.load(f)

		const = Consts(data[0]['Consts']['mem_size'],
		               data[0]['Consts']['cycle_delta'],
		               data[0]['Consts']['players_number'],
		               data[0]['Consts']['max_checks'],
		               data[0]['Consts']['const_nbr_live'],
		               data[0]['Consts']['const_cycle_to_die'])

		if ('State' in data[0]) & (data[0]['State']['error_code'] == 0):
			state = State(data[0]['State']['total_process'],
		               data[0]['State']['cycle_to_die'],
		               data[0]['State']['nbr_live'])
			window = MyGame(SCREEN_WIDTH + 500, SCREEN_HEIGHT, SCREEN_TITLE,
			                data, const, state)
			window.setup()
			arcade.run()


if __name__ == "__main__":
	main()