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

MEM_SIZE = 9900
ROWS = 100
COLS = 99
SQUARE_SPACING = 7

SCREEN_WIDTH = int(COLS * SQUARE_SPACING) + 20
SCREEN_HEIGHT = int(ROWS * SQUARE_SPACING) + 20
SCREEN_TITLE = "Arena"

#HALF_SQUARE = int((SQUARE_SPACING - 2) / 2) if SQUARE_SPACING % 2 == 0 else int((SQUARE_SPACING - 1) / 2)


COLOR_PLAYER = [arcade.color.RED, arcade.color.AMBER, arcade.color.BLUEBERRY]
COLOR_WRITE = [arcade.color.ALABAMA_CRIMSON, arcade.color.LEMON_GLACIER, arcade.color.GREEN, arcade.color.AQUA]


class Consts(object):
	def __init__(self, rows, cols, my_ch, opp_ch):
		self.rows = rows
		self.cols = cols
		self.my_ch = my_ch
		self.opp_ch = opp_ch
		self.height = 0
		self.width = 0
		self.sq_spacing = 7
		self.half_sq = 3

class Cells(object):
	def __init__(self, end_game, cycle, my_cells = None, opp_cells = None):
		self.end_game = end_game
		self.cycle = cycle
		self.my_cells = my_cells
		self.opp_cells = opp_cells


class MyGame(arcade.Window):

	def __init__(self, width, height, title, data, const):
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
		self.my_area = 0
		self.opp_area = 0
		self.const = const
		self.game_over = False


	def setup(self):
		self.shape_list = arcade.ShapeElementList()
		cnt = 0
		for y in range(self.const.height - 10 - self.const.half_sq, 10, -self.const.sq_spacing):
			for x in range(self.const.half_sq + 10, self.const.width-10, self.const.sq_spacing):

				top_left = (x - self.const.half_sq, y + self.const.half_sq)
				top_right = (x + self.const.half_sq, y + self.const.half_sq)
				bottom_right = (x + self.const.half_sq, y - self.const.half_sq)
				bottom_left = (x - self.const.half_sq, y - self.const.half_sq)

				self.point_list.append(top_left)
				self.point_list.append(top_right)
				self.point_list.append(bottom_right)
				self.point_list.append(bottom_left)

				for i in range(4):
					self.color_list.append(arcade.color.BATTLESHIP_GREY)
				cnt = cnt + 1
		shape = arcade.create_rectangles_filled_with_colors(self.point_list, self.color_list)
		self.shape_list.append(shape)


	def cell_refresh(self, data_cell, type):
		#print('cell_refresh')

		for j in range(0, len(data_cell)):
			start_place = (data_cell[j] - 1) * 4

			# меняю счетчик занятой игроком площади
			if type == 0:
				self.my_area += 1
			else:
				self.opp_area += 1
			# меняю цвет ячейки
			for n in range(0, 4):
				self.color_list[start_place + n] = COLOR_WRITE[type]

	def drop(self):

		# Cell color refresh
		#if self.data[self.json_indx]['cells_refresh'] > 0:
		self.cell_refresh(self.data[self.json_indx]['my_cells'], 0)
		self.cell_refresh(self.data[self.json_indx]['opp_cells'], 1)
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

		start_y -= 20
		mystr = 'SPEED:' + str(self.speed)
		arcade.draw_text(mystr, start_x, start_y, arcade.color.WHITE, 12)

		start_y -= 40
		mystr = 'cycle: ' + str(self.cycle)
		arcade.draw_text(mystr, start_x, start_y, arcade.color.WHITE, 12)
		start_y -= 50
		for i in range(0, 2):
			mystr = 'player: ' + str(i)
			arcade.draw_text(mystr, start_x, start_y, arcade.color.WHITE, 12)
			start_y -= 30
		#print('star_x =', start_x, 'start_y =', start_y)


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
			start_x += self.players[i].area / 10

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
		#self.draw_schem()
		self.draw_time = timeit.default_timer() - draw_start_time

	def update(self, delta_time):
		# print('update')

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
			dt = (3 if self.speed == -2 else 2)
			self.speed += dt
			if self.speed > 20:
				self.speed = 20
		elif key == arcade.key.DOWN:
			self.frame_count = 0
			self.speed -= (3 if self.speed == 2 else 2)
			if self.speed < -60:
				self.speed = -60



def main():
	pygame.init()
	pygame.mixer.music.load('sound/Secret_of_Mana_Desert_Snowstorm_OC_ReMix.mp3')
	pygame.mixer.music.play(- 1)
	with open('vis.json') as f:
		data = json.load(f)
	const = Consts(data[0]['Consts']['map_rows'],
		               data[0]['Consts']['map_cols'],
		               data[0]['Consts']['my_ch'],
		               data[0]['Consts']['opp_ch'])

	sq_spac_y = int(round(700 / const.rows))
	sq_spac_x = int(round(700 / const.cols))

	const.width = 700
	const.height = 700

	if sq_spac_x < sq_spac_y:
		const.sq_spacing = sq_spac_x
		#const.height = int(round((700*const.rows)/const.cols))
	else:
		const.sq_spacing = sq_spac_y
		#const.width = int(round((700 * const.cols) / const.rows))

	if const.sq_spacing % 2 == 0:
		const.half_sq = int((const.sq_spacing- 2) / 2)
	else:
		const.half_sq = int((const.sq_spacing - 1) / 2)

	const.height = const.sq_spacing * const.rows +20
	const.width = const.sq_spacing * const.cols + 20

	print("WIDTH =")
	print(const.width)
	print("HEIGHT:")
	print(const.height)
	print("sq_spacing")
	print(const.sq_spacing)
	print("half_sq")
	print(const.half_sq)
	ROWS = const.rows
	COLS = const.cols
	MEM_SIZE = const.rows * const.cols

	window = MyGame(const.width + 500, const.height, 'Arena',
			                data, const)
	window.setup()
	arcade.run()


if __name__ == "__main__":
	main()
