import numpy as np

# UNKNOWN: dame or seki
WHITE, EMPTY, BLACK, FILL, KO, UNKNOWN = range(-1, 5)
N = 4
ALL_COORDS = [(i, j) for i in range(N) for j in range(N)]
def _check_bounds(c):
    return 0 <= c[0] < N and 0 <= c[1] < N
NEIGHBORS = {(x, y): list(filter(_check_bounds, [
    (x+1, y), (x-1, y), (x, y+1), (x, y-1)])) for x, y in ALL_COORDS}

def find_reached(board, c):
    color = board[c]
    chain = set([c])
    reached = set()
    frontier = [c]
    while frontier:
        current = frontier.pop()
        chain.add(current)
        for n in NEIGHBORS[current]:
            if board[n] == color and not n in chain:
                frontier.append(n)
            elif board[n] != color:
                reached.add(n)
    return chain, reached

def place_stones(board, color, stones):
    for s in stones:
        board[s] = color

# board:    NxN numpy array(dtype=np.int8), 0 empty, 1 black, -1 white.
# komi:     int, 
def score(board, komi):
    working_board = np.copy(board)
    while EMPTY in working_board:
        unassigned_spaces = np.where(working_board == EMPTY)
        # c is the first empty stone in board, is a tuple
        c = (unassigned_spaces[0][0], unassigned_spaces[1][0])
        territory, borders = find_reached(working_board, c)
        border_colors = set(working_board[b] for b in borders)
        X_border = BLACK in border_colors
        O_border = WHITE in border_colors
        if X_border and not O_border:
            territory_color = BLACK
        elif O_border and not X_border:
            territory_color = WHITE
        else:
            territory_color = UNKNOWN  # dame, or seki
        place_stones(working_board, territory_color, territory)
    #return np.count_nonzero(working_board == BLACK) - np.count_nonzero(working_board == WHITE) - komi
    return np.count_nonzero(working_board == BLACK), np.count_nonzero(working_board == WHITE)

def produce_board():
    board = (np.random.random([N,N]) * 2 - 1).round().astype(np.int8)
    #board = np.zeros([N,N], dtype=np.int8)
    return board

if __name__ == "__main__":
    times = 10
    for i in range(times):
        board = produce_board()
        print board, score(board, 0)
        print ""
