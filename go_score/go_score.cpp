#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

#define N 4 //BORDER_SIZE

#define WHITE -1
#define EMPTY 0
#define BLACK 1
#define FILL 2
#define KO 3
#define UNKNOWN 4

int find_one_empty(vector<int>& board);
int count_black_win_num(vector<int>& board, int& b_num, int& w_num);
bool color_in_territory(vector<int>& board, vector<int>& set, int color);
int find_reached(vector<int>& board, int idx, vector<int>& territory, vector<int>& borders);
int score(vector<int>& board, int komi, int& b_num, int& w_num);
void get_neighbor(int idx, vector<int>& neighbors);
bool inside_board(int x, int y);
bool in_territory(vector<int>& territory, int idx);
void place_stones(vector<int>& working_board, int territory_color, vector<int> territory);
void make_board(vector<int>& board, int border_size, bool display);

int main(){
  vector<int> board;
  int b, w;
  make_board(board, N, true);
  score(board, 0, b, w);
  cout << " (B: " << b << ", W: " << w << ")" << endl;
  return 0;
}

void make_board(vector<int>& board, int border_size, bool display){
  srand((unsigned)time(NULL));
  board.clear();
  for (int i = 0; i < border_size*border_size; ++i){
    int r = rand();
    char color_c;
    int color;
    if (r < RAND_MAX / 5 * 2){
      color_c = 'B';
      color = -1;
    } else if (r > RAND_MAX / 5 * 3){
      color_c = 'W';
      color = 1;
    } else {
      color_c = '0';
      color = 0;
    }
    board.push_back(color);
    if (i % N == 0) cout << endl << color_c;
    else cout << ", " << color_c;
  }
}

int score(vector<int>& board, int komi, int& b_num, int& w_num){
  vector<int> working_board(N*N, 0);
  for (int i = 0; i < N*N; ++i){
    if (board[i] == -1 || board[i] == 0 || board[i] == 1){
      working_board[i] = board[i];
    }else{
      cout << "Wrong stone in input board: " << board[i] << endl;
      return -9998;
    }
  }
  vector<int> territory;
  vector<int> borders;
  while (find_one_empty(working_board) != -1){
    int em_id = find_one_empty(working_board);
    find_reached(working_board, em_id, territory, borders);
    if (color_in_territory(working_board, borders, EMPTY)){
      cout << "Wrong EMPTY in borders." << endl;
      return -9999;
    }
    bool black_in_border = color_in_territory(working_board, borders, BLACK);
    bool white_in_border = color_in_territory(working_board, borders, WHITE);
    int territory_color;
    if (black_in_border && !white_in_border){
      territory_color = BLACK;
    } else if (!black_in_border && white_in_border){
      territory_color = WHITE;
    } else {
      territory_color = UNKNOWN;
    }
    place_stones(working_board, territory_color, territory);
  }
  return count_black_win_num(working_board, b_num, w_num) - komi;
}

void place_stones(vector<int>& working_board, int territory_color, vector<int> territory){
  for (int i = 0; i < territory.size(); ++i){
    working_board[territory[i]] = territory_color;
  }
}

int find_reached(vector<int>& board, int idx, vector<int>& territory, vector<int>& borders){
  int color = board[idx];
  territory.clear();
  borders.clear();
  vector<int> frontier(1, idx);
  vector<int> neighbors;
  while (!frontier.empty()){
    int current = frontier.back();
    frontier.pop_back();
    territory.push_back(current);
    get_neighbor(current, neighbors);
    for (int i = 0; i < neighbors.size(); ++i){
      int nei_idx = neighbors[i];
      if (board[nei_idx] == color && !in_territory(territory, nei_idx)){
        frontier.push_back(nei_idx);
      }else if (board[nei_idx] != color){
        borders.push_back(nei_idx);
      }
    }
  }
  return territory.size();
}

bool in_territory(vector<int>& territory, int idx){
  for (int i = 0; i < territory.size(); ++i){
    if (territory[i] == idx){
      return true;
    }
  }
  return false;
}

void get_neighbor(int idx, vector<int>& neighbors){
  neighbors.clear();
  int y = idx / N;
  int x = idx % N;
  if (inside_board(x-1,y)){neighbors.push_back(idx-1);}
  if (inside_board(x+1,y)){neighbors.push_back(idx+1);}
  if (inside_board(x,y-1)){neighbors.push_back(idx-N);}
  if (inside_board(x,y+1)){neighbors.push_back(idx+N);}
}

bool inside_board(int x, int y){
  if (x >= 0 && x < N && y >= 0 && y < N){
    return true;
  }
  return false;
}

bool color_in_territory(vector<int>& board, vector<int>& set, int color){
  for (int i = 0; i < set.size(); ++i){
    if (board[set[i]] == color){
      return true;
    }
  }
  return false;
}

int count_black_win_num(vector<int>& board, int& b_num, int& w_num){
  int black = 0;
  int white = 0;
  for (int i = 0; i < N*N; ++i){
    if (board[i] == BLACK){
      black ++;
    } else if (board[i] == WHITE){
      white ++;
    }
  }
  b_num = black;
  w_num = white;
  return black - white;
}

int find_one_empty(vector<int>& board){
  for (int i = 0; i < N*N; ++i){
    if (board[i] == EMPTY){
      return i;
    }
  }
  return -1;
}
