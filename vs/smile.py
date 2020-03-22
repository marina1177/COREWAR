import code
from typing import List
import arcade
import timeit
import argparse
import sys
import codecs
import os

MAX_PLAYERS	= 4
MEM_SIZE = (4*1024)
MAX_ARGS_NUMBER = 4
IDX_MOD = (MEM_SIZE / 8)
CHAMP_MAX_SIZE = (MEM_SIZE / 6)

CYCLE_TO_DIE = 1536
CYCLE_DELTA = 50
NBR_LIVE = 21
MAX_CHECKS = 10

PROG_NAME_LENGTH = 128
COMMENT_LENGTH = 2048

EXEC_START = (4 + PROG_NAME_LENGTH + 4 + 4 + COMMENT_LENGTH + 4)
FULL_SIZE = (EXEC_START + CHAMP_MAX_SIZE)

T_REG=1
T_DIR=2
T_IND=4
"""***********************************************************************************************"""
RUNNING 	= 713
CYCLE_PER_SEC = 1225
CYCLE_COORD	= 1993
PROCESSES = 2505
PL_ONE_LIVE	=3529

"""
LIVE_CODE   =0x01
LD_CODE     =0x02
ST_CODE 	=0x03
ADD_CODE	=0x04
SUB_CODE	=0x05
AND_CODE	=0x06
OR_CODE	    =0x07
XOR_CODE	=0x08
ZJMP_CODE	=0x09
LDI_CODE	=0x0a
STI_CODE	=0x0b
FORK_CODE	=0x0c
LLD_CODE	=0x0d
LLDI_CODE	=0x0e
LFORK_CODE	=0x0f
AFF_CODE	=0x10  """

LIVE_CYCLE_CD  =10
LD_CYCLE_CD	   =5
ST_CYCLE_CD    =5
ADD_CYCLE_CD   =10
SUB_CYCLE_CD=	10
AND_CYCLE_CD=	6
OR_CYCLE_CD	   = 6
XOR_CYCLE_CD=	6
ZJMP_CYCLE_CD=	20
LDI_CYCLE_CD=	25
STI_CYCLE_CD=	25
FORK_CYCLE_CD=	800
LLD_CYCLE_CD=	10
LLDI_CYCLE_CD=	50
LFORK_CYCLE_CD=	1000
AFF_CYCLE_CD=	2

SCREEN_WIDTH = 960
SCREEN_HEIGHT = 960
SCREEN_TITLE = "ARENA"

HALF_SQUARE_WIDTH = 7
HALF_SQUARE_HEIGHT = 7
SQUARE_SPACING = 15

COLOR_PLAYER = ['RED', 'LIME', 'YELLOW', 'CYAN']
#class Arena(object):


class Option(object):
    def __init__(self, name=None, code=0, args_num = 0,
                 args_types_code = False,args_types = [0, 0, 0], t_dir_size = 0):
        self.name = name
        self.code = code
        self.args_num = args_num
        self.args_types_code = args_types_code
        self.args_types = args_types
        self.t_dir_size = t_dir_size

def create_tab():
    OpTab =[]
    OpTab.append(Option('live', 1, 1, False, [T_DIR, 0, 0], 4))
    OpTab.append(Option('ld', 2, 2, True, [T_DIR | T_IND, T_REG, 0], 4))
    OpTab.append(Option('st', 3, 2, True, [T_REG, T_REG | T_IND, 0], 4))
    OpTab.append(Option('add', 4, 3, True, [T_REG, T_REG, T_REG], 4))
    OpTab.append(Option('sub', 5, 3, True, [T_REG, T_REG, T_REG], 4))
    OpTab.append(Option('and', 6, 3, True, [T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG], 4))
    OpTab.append(Option('or', 7, 3, True, [T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG], 4))
    OpTab.append(Option('xor', 8, 3, True, [T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG], 4))
    OpTab.append(Option('zjmp', 9, 1, False, [T_DIR, 0, 0], 2))
    OpTab.append(Option('ldi', 10, 3, True, [T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG], 2))
    OpTab.append(Option('sti', 11, 3, True, [T_REG, T_REG | T_DIR | T_IND, T_REG | T_DIR], 2))
    OpTab.append(Option('fork', 12, 1, False, [T_DIR, 0, 0], 2))
    OpTab.append(Option('lld', 13, 2, True, [T_DIR | T_IND, T_REG, 0], 4))
    OpTab.append(Option('lldi', 14, 3, True, [T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG], 2))
    OpTab.append(Option('lfork', 15, 1, False, [T_DIR, 0, 0], 2))
    OpTab.append(Option('aff', 16, 1, True, [T_REG, 0, 0], 4))
    return (OpTab)

G_OP_TAB = create_tab()

class Champion(object):
    def __init__(self, name=None, comment=None,size_code=0, code = None):
        self.name = name
        self.comment = comment
        self.size_code = size_code
        self.code = code


class Carriage(object):
    def __init__(self, num =-1, carry=0,
                 regs=[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0], op_code=0, live_cycle=0):
        self.num = num
        self.carry = carry
        self.regs = regs
        self.op_code = op_code
        self.live_cycle = live_cycle

class MyGame(arcade.Window):
    """ Main application class. """

    def __init__(self, width, height, title, players):
        super().__init__(width, height, title)
        arcade.set_background_color(arcade.color.BLACK)
        self.draw_time = 0
        self.shape_list = None
        self.players = players
        self.num_pl = len(players)
        self.arena =bytearray(4096)

    def setup(self):
        """print("len players:")
        print(int(self.num_pl))"""
        delta = MEM_SIZE / self.num_pl
        start_code=[]
        for i in range(0, MEM_SIZE, round(delta)):
            start_code.append(i)
            print(i)

        self.shape_list = arcade.ShapeElementList()
        point_list = []
        color_list = []
        cnt = 0
        # Now calculate all the points

        for x in range(HALF_SQUARE_WIDTH, SCREEN_WIDTH, SQUARE_SPACING):
            for y in range(HALF_SQUARE_HEIGHT, SCREEN_HEIGHT, SQUARE_SPACING):

                # Calculate where the four points of the rectangle will be if
                # x and y are the center
                top_left = (x - HALF_SQUARE_WIDTH, y + HALF_SQUARE_HEIGHT)
                top_right = (x + HALF_SQUARE_WIDTH, y + HALF_SQUARE_HEIGHT)
                bottom_right = (x + HALF_SQUARE_WIDTH, y - HALF_SQUARE_HEIGHT)
                bottom_left = (x - HALF_SQUARE_WIDTH, y - HALF_SQUARE_HEIGHT)

                # Add the points to the points list.
                # ORDER MATTERS!
                # Rotate around the rectangle, don't append points caty-corner
                point_list.append(top_left)
                point_list.append(top_right)
                point_list.append(bottom_right)
                point_list.append(bottom_left)

                # Add a color for each point. Can be different colors if you want
                # gradients.
                for i in range(4):
                    #color_list.append(arcade.color.DARK_BLUE)
                    for k in range (0, len(start_code)):

                        if (cnt >= start_code[k]) & (cnt < self.players[k].size_code + start_code[k]):
                            print(cnt, "-red")
                            if cnt == start_code[k]:
                                color_list.append(arcade.color.BLACK)
                            else:
                                color_list.append(arcade.color.RED)
                        else:
                           # print(cnt, "-blue")
                            color_list.append(arcade.color.WHITE)
                cnt = cnt + 1

        shape = arcade.create_rectangles_filled_with_colors(point_list, color_list)
        self.shape_list.append(shape)
        pass

    def on_draw(self):
        # This command has to happen before we start drawing
        arcade.start_render()

        # Start timing how long this takes
        draw_start_time = timeit.default_timer()

        # --- Draw all the rectangles
        self.shape_list.draw()
        output = f"Drawing time: {self.draw_time:.3f} seconds per frame."
        arcade.draw_text(output, 20, SCREEN_HEIGHT - 40, arcade.color.WHITE, 18)
        self.draw_time = timeit.default_timer() - draw_start_time

    def update(self, delta_time):
        pass
    #    print("game")
        """ Здесь вся игровая логика и логика перемещения."""



#john = Employee('John Johnson',  3000)

def main():
    #champs = parse_champs()
    ChampArr = []
    ac = len(sys.argv)
    for i in range(1, ac):
        print("Argument List:", str(sys.argv[i]))
        with open(str(sys.argv[i]), "rb") as binary_file:
            # Read the whole file at once
            data = binary_file.read(4)
            print(data)

            name = binary_file.read(128)
            print(name.decode('utf-8'))

            binary_file.read(4)

            code_size = binary_file.read(4)
            print(int.from_bytes(code_size, byteorder='big', signed=True))

            comment = binary_file.read(2048)
            print(comment.decode('utf-8'))

            test_code = os.stat(str(sys.argv[i])).st_size - 2192
            """if  (test_code != code_size)
                print("Error exec size code!")"""
            binary_file.read(4)
            code = binary_file.read()
            print(code)
            player = Champion(name.decode('utf-8'), comment.decode('utf-8'),
                              ((os.stat(str(sys.argv[i]))).st_size - 2192), code)
            ChampArr.append(player)

    print("len champs:")
    print(len(ChampArr))
    window = MyGame(SCREEN_WIDTH+400, SCREEN_HEIGHT, SCREEN_TITLE, ChampArr)
    window.setup()
    arcade.run()

if __name__ == "__main__":
    main()
# print(parser)
