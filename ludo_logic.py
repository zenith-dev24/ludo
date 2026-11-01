import random

TOTAL_TRACK_TILES = 52
SAFE_TILES = [0,8,13,21,26,34,39,47]

class Token:
    def __init__(self,token__id,color):
        self.token_id = token_id
        self.state = "BASE" #BASE,MAIN_PATH,HOME_PATH,FINISHED
        self.steps_taken = 0

class Player:
    def __init__(self,color,start_position):
        self.color = color
        self.start_position = start_pos
        self.name = name
        self.tokens = [Token(i) for i in range(4)]

    def has_won(self):
        return all(t.state == "FINISHED" for t in self.tokens)

class LudoGame:
    def __init__(self,num_players):
        self.players = []
        self.current_player_index = 0
        self.current_roll = 0
        self.needs_to_roll = True
        self.game_over = False

        start