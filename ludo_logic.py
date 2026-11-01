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

        start_positions = {"RED":0,"BLUE":13,"YELLOW":26,"GREEN":39}

        for p in active_players:
            self.players.append(Player(p["color"],start_positions[p["color"]],p["name"]))

    def roll_dice(self):
        self.current_roll = random.randint(1,6)
        self.needs_to_roll = False

    def get_absolute_position(self,start_position,steps_taken):
        return (start_position + steps_taken) % TOTAL_TRACK_TILES

    def is_safe_square(self,abs_pos):
        return abs_pos in SAFE_TILES

    def handle_capture(self,target_abs_pos,moving_color):
        if self.is_safe_square(target_abs_pos):
            return
        for player in self.players:
            if player.color == moving_color:
                continue
            for token in player.tokens:
                if token.state == "MAIN_PATH":
                    token_abs_pos = self.get_absolute_position(player.start_position,token.steps_taken)
                    if token_abs_pos == target_abs_pos:
                        token.state = "BASE"
                        token.steps_taken = 0

    def try_move_token(self,token):
        
    def has_valid_moves(self):
        current = self.players[self.current_player_index]
        for t in current.tokens:
            if t.state == "BASE" and self.current_player_index == 6:
                return True
            if t.state == "MAIN_PATH" and t.steps_taken + self.current_roll <= 56:
                return True
            if t.state == "HOME_PATH" and t.steps_taken + self.current_roll <= 56:
                return True
        return False
                
