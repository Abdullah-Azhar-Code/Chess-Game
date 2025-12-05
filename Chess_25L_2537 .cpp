#include<iostream>
#include<string>
#include <SFML/Graphics.hpp>
#include<sfml/Window.hpp>
#include<sfml/System.hpp>
#include<SFML/Audio.hpp>
#include<sfml/Network.hpp>

using namespace std;
using namespace sf;

Font font;
Text turnText;
Text statusText;
Text whiteCapturedLabel;
Text blackCapturedLabel;
RectangleShape rightPanel;
int whiteCapCount = 0;
int blackCapCount = 0;
string whiteCaptured[32];
string blackCaptured[32];

Texture pawn_white, pawn_black;
Texture rook_white, rook_black;
Texture knight_white, knight_black;
Texture bishop_white, bishop_black;
Texture queen_white, queen_black;
Texture king_white, king_black;
Sprite chessboard_pieces[8][8];
string pieces_names[8][8];
int valid_moves[64][2]; //0th index for storing row and 1th index for storing columns.
int count_moves = 0;
int selected_row = -1, piece_row = -1;
int selected_column = -1, piece_column = -1;
int sx, sy;
int dx, dy;
string piece_color;
string current_turn = "White";
bool white_in_check = false;
bool black_in_check = false;
bool game_over = false;

bool loading_texture()
{
	bool loaded = true;
	//Loading textures from file (chess_pieces)
	pawn_white.loadFromFile("chess_pieces/pawn_white.png");
	pawn_black.loadFromFile("chess_pieces/pawn_black.png");
	rook_white.loadFromFile("chess_pieces/rook_white.png");
	rook_black.loadFromFile("chess_pieces/rook_black.png");
	knight_white.loadFromFile("chess_pieces/knight_white.png");
	knight_black.loadFromFile("chess_pieces/knight_black.png");
	bishop_white.loadFromFile("chess_pieces/bishop_white.png");
	bishop_black.loadFromFile("chess_pieces/bishop_black.png");
	queen_white.loadFromFile("chess_pieces/queen_white.png");
	queen_black.loadFromFile("chess_pieces/queen_black.png");
	king_white.loadFromFile("chess_pieces/king_white.png");
	king_black.loadFromFile("chess_pieces/king_black.png");

	//Checking if there is any error in loading textures through if conditions.
	if (!pawn_white.loadFromFile("chess_pieces/pawn_white.png"))
	{
		cout << "Error_loading chess_pieces/pawn_white.png" << endl;
		loaded = false;
	}
	if (!pawn_black.loadFromFile("chess_pieces/pawn_black.png"))
	{
		cout << "Error_loading chess_pieces/pawn_black.png" << endl;
		loaded = false;
	}
	if (!rook_white.loadFromFile("chess_pieces/rook_white.png"))
	{
		cout << "Error_loading chess_pieces/rook_white.png" << endl;
		loaded = false;
	}
	if (!rook_black.loadFromFile("chess_pieces/rook_black.png"))
	{
		cout << "Error_loading chess_pieces/rook_black.png" << endl;
		loaded = false;
	}
	if (!knight_white.loadFromFile("chess_pieces/knight_white.png"))
	{
		cout << "Error_loading chess_pieces/knight_white.png" << endl;
		loaded = false;
	}
	if (!knight_black.loadFromFile("chess_pieces/knight_black.png"))
	{
		cout << "Error_loading chess_pieces/knight_black.png" << endl;
		loaded = false;
	}
	if (!bishop_white.loadFromFile("chess_pieces/bishop_white.png"))
	{
		cout << "Error_loading chess_pieces/bishop_white.png" << endl;
		loaded = false;
	}
	if (!bishop_black.loadFromFile("chess_pieces/bishop_black.png"))
	{
		cout << "Error_loading chess_pieces/bishop_black.png" << endl;
		loaded = false;
	}
	if (!queen_white.loadFromFile("chess_pieces/queen_white.png"))
	{
		cout << "Error_loading chess_pieces/queen_white.png" << endl;
		loaded = false;
	}
	if (!queen_black.loadFromFile("chess_pieces/queen_black.png"))
	{
		cout << "Error_loading chess_pieces/queen_black.png" << endl;
		loaded = false;
	}
	if (!king_white.loadFromFile("chess_pieces/king_white.png"))
	{
		cout << "Error_loading chess_pieces/king_white.png" << endl;
		loaded = false;
	}
	if (!king_black.loadFromFile("chess_pieces/king_black.png"))
	{
		cout << "Error_loading chess_pieces/king_black.png" << endl;
		loaded = false;
	}
	return loaded;
}
void piece_name(RenderWindow& window)
{
	pieces_names[0][0] = "Black Rook";
	pieces_names[0][1] = "Black Knight";
	pieces_names[0][2] = "Black Bishop";
	pieces_names[0][3] = "Black Queen";
	pieces_names[0][4] = "Black King";
	pieces_names[0][5] = "Black Bishop";
	pieces_names[0][6] = "Black Knight";
	pieces_names[0][7] = "Black Rook";
	for (int column = 0; column < 8; column++) //For pawns
	{
		pieces_names[1][column] = "Black Pawn";
	}
	for (int column = 0; column < 8; column++) //For pawns
	{
		pieces_names[6][column] = "White Pawn";
	}
	pieces_names[7][0] = "White Rook";
	pieces_names[7][1] = "White Knight";
	pieces_names[7][2] = "White Bishop";
	pieces_names[7][3] = "White Queen";
	pieces_names[7][4] = "White King";
	pieces_names[7][5] = "White Bishop";
	pieces_names[7][6] = "White Knight";
	pieces_names[7][7] = "White Rook";
}
void setting_chessboard_pieces(RenderWindow& window, float square_size)
{
	//black pieces
	chessboard_pieces[0][0].setTexture(rook_black);
	chessboard_pieces[0][1].setTexture(knight_black);
	chessboard_pieces[0][2].setTexture(bishop_black);
	chessboard_pieces[0][3].setTexture(queen_black);
	chessboard_pieces[0][4].setTexture(king_black);
	chessboard_pieces[0][5].setTexture(bishop_black);
	chessboard_pieces[0][6].setTexture(knight_black);
	chessboard_pieces[0][7].setTexture(rook_black);
	for (int column = 0; column < 8; column++) //For pawns
	{
		chessboard_pieces[1][column].setTexture(pawn_black);
	}

	//white pieces
	for (int column = 0; column < 8; column++) //For pawns
	{
		chessboard_pieces[6][column].setTexture(pawn_white);
	}
	chessboard_pieces[7][0].setTexture(rook_white);
	chessboard_pieces[7][1].setTexture(knight_white);
	chessboard_pieces[7][2].setTexture(bishop_white);
	chessboard_pieces[7][3].setTexture(queen_white);
	chessboard_pieces[7][4].setTexture(king_white);
	chessboard_pieces[7][5].setTexture(bishop_white);
	chessboard_pieces[7][6].setTexture(knight_white);
	chessboard_pieces[7][7].setTexture(rook_white);

	for (int row = 0; row < 8; row++)
	{
		for (int column = 0; column < 8; column++)
		{
			chessboard_pieces[row][column].setScale(1.85f, 1.85f); //I have done it because the size of chessboard pices was small.
		}
	}
}

void draw_pieces(RenderWindow& window, float square_size)
{
	for (int row = 0; row < 8; row++)
	{
		for (int column = 0; column < 8; column++)
		{
			if (pieces_names[row][column] != "")
			{
				chessboard_pieces[row][column].setPosition(static_cast<float>(column) * square_size, static_cast<float>(row) * square_size);
				window.draw(chessboard_pieces[row][column]);
			}
		}
	}
}
void Chess_Board(RenderWindow& window, float square_size)
{
	for (int row = 0; row < 8; row++)
	{
		for (int column = 0; column < 8; column++)
		{
			RectangleShape square(Vector2f(square_size, square_size));
			square.setPosition(static_cast<float>(column) * square_size, static_cast<float>(row) * square_size);
			// value of column will correspond to x axis value. increase will move right and decrease will move left.
			// value of row will correspond to y axis value. increase will move down and decrease will move up.
			if (row % 2 == column % 2)
			{
				square.setFillColor(Color::Black);
			}
			else
			{
				square.setFillColor(Color::White);
			}
			window.draw(square);
		}
	}
}
void pawn_capture_moves(int source_rows, int source_columns, string piece_color)
{
	int fy[2] = { source_columns - 1,source_columns + 1 };
	for (int i = 0; i < 2; i++)
	{
		int direction = 0;
		if (piece_color == "White")
		{
			direction = -1;
		}
		else
		{
			direction = 1;
		}
		int fx = direction + source_rows;

		int dy = fy[i];
		if (fx >= 0 && fx <= 7 && dy >= 0 && dy <= 7)
		{
			if (pieces_names[fx][dy] != "" && pieces_names[fx][dy].find(piece_color) == string::npos)
			{
				valid_moves[count_moves][0] = fx;
				valid_moves[count_moves][1] = dy;
				count_moves++;
			}
		}
	}
}
void check_pawn_moves(int source_rows, int source_columns, string piece_color)
{
	count_moves = 0;
	int direction = 0;
	if (piece_color == "White")
	{
		direction = -1;
	}
	else
	{
		direction = 1;
	}
	int fx = direction + source_rows;
	if (fx >= 0 && fx <= 7 && pieces_names[fx][source_columns] == "")
	{
		valid_moves[count_moves][0] = fx;
		valid_moves[count_moves][1] = source_columns;
		count_moves++;
	}
	int fx2 = source_rows + 2 * direction; //Multiplying by two to move pawn 2 places forward
	if ((piece_color == "White" && source_rows == 6) || (piece_color == "Black" && source_rows == 1))
	{
		int fx2 = source_rows + 2 * direction; //Multiplying by two to move pawn 2 places forward
		if (pieces_names[fx2][source_columns] == "" && pieces_names[fx2 - direction][source_columns] == "")
		{
			valid_moves[count_moves][0] = fx2;
			valid_moves[count_moves][1] = source_columns;
			count_moves++;
		}
	}
	//Now checking for capturing of pawn as it captures diagonally
	pawn_capture_moves(source_rows, source_columns, piece_color);
}
void pawn_promotion(int row, int column, string piece_color)
{
	if (piece_color == "White" && row == 0)
	{
		chessboard_pieces[row][column].setTexture(queen_white);
		chessboard_pieces[row][column].setScale(1.85f, 1.85f);
		pieces_names[row][column] = "White Queen";
	}
	else if (piece_color == "Black" && row == 7)
	{
		chessboard_pieces[row][column].setTexture(queen_black);
		chessboard_pieces[row][column].setScale(1.85f, 1.85f);
		pieces_names[row][column] = "Black Queen";
	}
}
void check_rook_moves(int source_rows, int source_columns, string piece_color)
{
	count_moves = 0;
	int fx1 = source_rows + 1;
	int fx2 = source_rows - 1;
	int fy1 = source_columns + 1;
	int fy2 = source_columns - 1;

	while (fx1 >= 0 && fx1 <= 7) //All upper moves
	{
		if (pieces_names[fx1][source_columns] == "") //Checking empty square
		{
			valid_moves[count_moves][0] = fx1;
			valid_moves[count_moves][1] = source_columns;
			count_moves++;
			fx1++;
		}
		else if (pieces_names[fx1][source_columns].find(piece_color) == string::npos) //Checking different color
		{
			valid_moves[count_moves][0] = fx1;
			valid_moves[count_moves][1] = source_columns;
			count_moves++;
			fx1++;
			break;
		}
		else //If same color piece
		{
			break;
		}
	}

	while (fx2 >= 0 && fx2 <= 7) //All lower moves
	{
		if (pieces_names[fx2][source_columns] == "") //Checking empty square
		{
			valid_moves[count_moves][0] = fx2;
			valid_moves[count_moves][1] = source_columns;
			fx2--;
			count_moves++;
		}
		else if (pieces_names[fx2][source_columns].find(piece_color) == string::npos) //Checking different color
		{
			valid_moves[count_moves][0] = fx2;
			valid_moves[count_moves][1] = source_columns;
			fx2--;
			count_moves++;
			break;
		}
		else //If same color piece
		{
			break;
		}
	}

	while (fy1 >= 0 && fy1 <= 7) //All right moves
	{
		if (pieces_names[source_rows][fy1] == "") //Checking empty square
		{
			valid_moves[count_moves][0] = source_rows;
			valid_moves[count_moves][1] = fy1;
			fy1++;
			count_moves++;
		}
		else if (pieces_names[source_rows][fy1].find(piece_color) == string::npos) //Checking different color
		{
			valid_moves[count_moves][0] = source_rows;
			valid_moves[count_moves][1] = fy1;
			fy1++;
			count_moves++;
			break;
		}
		else //If same color piece
		{
			break;
		}
	}

	while (fy2 >= 0 && fy2 <= 7) //All left moves
	{
		if (pieces_names[source_rows][fy2] == "") //Checking empty square
		{
			valid_moves[count_moves][0] = source_rows;
			valid_moves[count_moves][1] = fy2;
			fy2--;
			count_moves++;
		}
		else if (pieces_names[source_rows][fy2].find(piece_color) == string::npos) //Checking different color
		{
			valid_moves[count_moves][0] = source_rows;
			valid_moves[count_moves][1] = fy2;
			fy2--;
			count_moves++;
			break;
		}
		else //If same color piece
		{
			break;
		}
	}
}
void check_knight_moves(int source_rows, int source_columns, string piece_color)
{
	int fx1 = source_rows - 2;
	int fx2 = source_rows + 2;
	int fx3 = source_rows - 1;
	int fx4 = source_rows + 1;
	int fy1 = source_columns - 1;
	int fy2 = source_columns + 1;
	int fy3 = source_columns - 2;
	int fy4 = source_columns + 2;
	count_moves = 0;

	if (fx1 >= 0 && fx1 <= 7) //Upper bound
	{
		if (fy1 >= 0 && fy1 <= 7) //Left bound
		{
			if (pieces_names[fx1][fy1] == "" || pieces_names[fx1][fy1].find(piece_color) == string::npos) //Checking empty square or different color
			{
				valid_moves[count_moves][0] = fx1;
				valid_moves[count_moves][1] = fy1;
				count_moves++;
			}
		}
		if (fy2 >= 0 && fy2 <= 7) //Right bound
		{
			if (pieces_names[fx1][fy2] == "" || pieces_names[fx1][fy2].find(piece_color) == string::npos) //Checking empty square or different color
			{
				valid_moves[count_moves][0] = fx1;
				valid_moves[count_moves][1] = fy2;
				count_moves++;
			}
		}
	}

	if (fx2 >= 0 && fx2 <= 7) //Lower bound
	{
		if (fy1 >= 0 && fy1 <= 7) //Left bound
		{
			if (pieces_names[fx2][fy1] == "" || pieces_names[fx2][fy1].find(piece_color) == string::npos) //Checking empty square or different color
			{
				valid_moves[count_moves][0] = fx2;
				valid_moves[count_moves][1] = fy1;
				count_moves++;
			}
		}
		if (fy2 >= 0 && fy2 <= 7) //Right bound
		{
			if (pieces_names[fx2][fy2] == "" || pieces_names[fx2][fy2].find(piece_color) == string::npos) //Checking empty square or different color
			{
				valid_moves[count_moves][0] = fx2;
				valid_moves[count_moves][1] = fy2;
				count_moves++;
			}
		}
	}

	if (fy3 >= 0 && fy3 <= 7) //Left bound
	{
		if (fx3 >= 0 && fx3 <= 7) //Upper bound
		{
			if (pieces_names[fx3][fy3] == "" || pieces_names[fx3][fy3].find(piece_color) == string::npos) //Checking empty square or different color
			{
				valid_moves[count_moves][0] = fx3;
				valid_moves[count_moves][1] = fy3;
				count_moves++;
			}
		}
		if (fx4 >= 0 && fx4 <= 7) //Lower bound
		{
			if (pieces_names[fx4][fy3] == "" || pieces_names[fx4][fy3].find(piece_color) == string::npos) //Checking empty square or different color
			{
				valid_moves[count_moves][0] = fx4;
				valid_moves[count_moves][1] = fy3;
				count_moves++;
			}
		}
	}

	if (fy4 >= 0 && fy4 <= 7) //Right bound
	{
		if (fx3 >= 0 && fx3 <= 7) //Upper bound
		{
			if (pieces_names[fx3][fy4] == "" || pieces_names[fx3][fy4].find(piece_color) == string::npos) //Checking empty square or different color
			{
				valid_moves[count_moves][0] = fx3;
				valid_moves[count_moves][1] = fy4;
				count_moves++;
			}
		}
		if (fx4 >= 0 && fx4 <= 7) //Lower bound
		{
			if (pieces_names[fx4][fy4] == "" || pieces_names[fx4][fy4].find(piece_color) == string::npos) //Checking empty square or different color
			{
				valid_moves[count_moves][0] = fx4;
				valid_moves[count_moves][1] = fy4;
				count_moves++;
			}
		}
	}
}
void check_bishop_moves(int source_rows, int source_columns, string piece_color)
{
	int fx1 = source_rows - 1;
	int fx2 = source_rows + 1;
	int fy1 = source_columns + 1;
	int fy2 = source_columns - 1;
	count_moves = 0;

	for (int row = fx1, column = fy1; row >= 0 && row <= 7 && column >= 0 && column <= 7; row--, column++) //All upper right diagonal moves
	{
		if (pieces_names[row][column] == "")
		{
			valid_moves[count_moves][0] = row;
			valid_moves[count_moves][1] = column;
			count_moves++;
		}
		else if (pieces_names[row][column].find(piece_color) == string::npos)
		{
			valid_moves[count_moves][0] = row;
			valid_moves[count_moves][1] = column;
			count_moves++;
			break;
		}
		else
		{
			break;
		}
	}

	for (int row = fx1, column = fy2; row >= 0 && row <= 7 && column >= 0 && column <= 7; row--, column--) //All upper left diagonal moves
	{
		if (pieces_names[row][column] == "")
		{
			valid_moves[count_moves][0] = row;
			valid_moves[count_moves][1] = column;
			count_moves++;
		}
		else if (pieces_names[row][column].find(piece_color) == string::npos)
		{
			valid_moves[count_moves][0] = row;
			valid_moves[count_moves][1] = column;
			count_moves++;
			break;
		}
		else
		{
			break;
		}
	}

	for (int row = fx2, column = fy1; row >= 0 && row <= 7 && column >= 0 && column <= 7; row++, column++) //All lower right diagonl moves
	{
		if (pieces_names[row][column] == "")
		{
			valid_moves[count_moves][0] = row;
			valid_moves[count_moves][1] = column;
			count_moves++;
		}
		else if (pieces_names[row][column].find(piece_color) == string::npos)
		{
			valid_moves[count_moves][0] = row;
			valid_moves[count_moves][1] = column;
			count_moves++;
			break;
		}
		else
		{
			break;
		}
	}

	for (int row = fx2, column = fy2; row >= 0 && row <= 7 && column >= 0 && column <= 7; row++, column--) //All lower left diagonal moves
	{
		if (pieces_names[row][column] == "")
		{
			valid_moves[count_moves][0] = row;
			valid_moves[count_moves][1] = column;
			count_moves++;
		}
		else if (pieces_names[row][column].find(piece_color) == string::npos)
		{
			valid_moves[count_moves][0] = row;
			valid_moves[count_moves][1] = column;
			count_moves++;
			break;
		}
		else
		{
			break;
		}
	}
}
void check_queen_moves(int source_rows, int source_columns, string piece_color)
{
	// Rook moves

	count_moves = 0;
	int fx1 = source_rows + 1;
	int fx2 = source_rows - 1;
	int fy1 = source_columns + 1;
	int fy2 = source_columns - 1;

	while (fx1 >= 0 && fx1 <= 7) //All upper moves
	{
		if (pieces_names[fx1][source_columns] == "")
		{
			valid_moves[count_moves][0] = fx1;
			valid_moves[count_moves][1] = source_columns;
			count_moves++;
			fx1++;
		}
		else if (pieces_names[fx1][source_columns].find(piece_color) == string::npos)
		{
			valid_moves[count_moves][0] = fx1;
			valid_moves[count_moves][1] = source_columns;
			count_moves++;
			fx1++;
			break;
		}
		else
		{
			break;
		}
	}

	while (fx2 >= 0 && fx2 <= 7) //All lower moves
	{
		if (pieces_names[fx2][source_columns] == "")
		{
			valid_moves[count_moves][0] = fx2;
			valid_moves[count_moves][1] = source_columns;
			fx2--;
			count_moves++;
		}
		else if (pieces_names[fx2][source_columns].find(piece_color) == string::npos)
		{
			valid_moves[count_moves][0] = fx2;
			valid_moves[count_moves][1] = source_columns;
			fx2--;
			count_moves++;
			break;
		}
		else
		{
			break;
		}
	}

	while (fy1 >= 0 && fy1 <= 7) //All right moves
	{
		if (pieces_names[source_rows][fy1] == "")
		{
			valid_moves[count_moves][0] = source_rows;
			valid_moves[count_moves][1] = fy1;
			fy1++;
			count_moves++;
		}
		else if (pieces_names[source_rows][fy1].find(piece_color) == string::npos)
		{
			valid_moves[count_moves][0] = source_rows;
			valid_moves[count_moves][1] = fy1;
			fy1++;
			count_moves++;
			break;
		}
		else
		{
			break;
		}
	}

	while (fy2 >= 0 && fy2 <= 7) //All left moves
	{
		if (pieces_names[source_rows][fy2] == "")
		{
			valid_moves[count_moves][0] = source_rows;
			valid_moves[count_moves][1] = fy2;
			fy2--;
			count_moves++;
		}
		else if (pieces_names[source_rows][fy2].find(piece_color) == string::npos)
		{
			valid_moves[count_moves][0] = source_rows;
			valid_moves[count_moves][1] = fy2;
			fy2--;
			count_moves++;
			break;
		}
		else
		{
			break;
		}
	}

	// Bishop moves

	int fx3 = source_rows - 1;
	int fx4 = source_rows + 1;
	int fy3 = source_columns + 1;
	int fy4 = source_columns - 1;

	for (int row = fx3, column = fy3; row >= 0 && row <= 7 && column >= 0 && column <= 7; row--, column++) //All upper right diagonal moves
	{
		if (pieces_names[row][column] == "")
		{
			valid_moves[count_moves][0] = row;
			valid_moves[count_moves][1] = column;
			count_moves++;
		}
		else if (pieces_names[row][column].find(piece_color) == string::npos)
		{
			valid_moves[count_moves][0] = row;
			valid_moves[count_moves][1] = column;
			count_moves++;
			break;
		}
		else
		{
			break;
		}
	}

	for (int row = fx3, column = fy4; row >= 0 && row <= 7 && column >= 0 && column <= 7; row--, column--) //All upper left diagonal moves
	{
		if (pieces_names[row][column] == "")
		{
			valid_moves[count_moves][0] = row;
			valid_moves[count_moves][1] = column;
			count_moves++;
		}
		else if (pieces_names[row][column].find(piece_color) == string::npos)
		{
			valid_moves[count_moves][0] = row;
			valid_moves[count_moves][1] = column;
			count_moves++;
			break;
		}
		else
		{
			break;
		}
	}

	for (int row = fx4, column = fy3; row >= 0 && row <= 7 && column >= 0 && column <= 7; row++, column++) //All lower right diagonal moves
	{
		if (pieces_names[row][column] == "")
		{
			valid_moves[count_moves][0] = row;
			valid_moves[count_moves][1] = column;
			count_moves++;
		}
		else if (pieces_names[row][column].find(piece_color) == string::npos)
		{
			valid_moves[count_moves][0] = row;
			valid_moves[count_moves][1] = column;
			count_moves++;
			break;
		}
		else
		{
			break;
		}
	}

	for (int row = fx4, column = fy4; row >= 0 && row <= 7 && column >= 0 && column <= 7; row++, column--) //All lower left diagonal moves
	{
		if (pieces_names[row][column] == "")
		{
			valid_moves[count_moves][0] = row;
			valid_moves[count_moves][1] = column;
			count_moves++;
		}
		else if (pieces_names[row][column].find(piece_color) == string::npos)
		{
			valid_moves[count_moves][0] = row;
			valid_moves[count_moves][1] = column;
			count_moves++;
			break;
		}
		else
		{
			break;
		}
	}
}
void check_king_moves(int source_rows, int source_columns, string piece_color)
{
	int fx1 = source_rows - 1;
	int fx2 = source_rows + 1;
	int fy1 = source_columns + 1;
	int fy2 = source_columns - 1;
	count_moves = 0;

	if (fx1 >= 0 && fx1 <= 7) //Upper row
	{
		if (pieces_names[fx1][source_columns] == "" || pieces_names[fx1][source_columns].find(piece_color) == string::npos)
		{
			valid_moves[count_moves][0] = fx1;
			valid_moves[count_moves][1] = source_columns;
			count_moves++;
		}
		if (fy2 >= 0 && fy2 <= 7) //Left diagonal
		{
			if (pieces_names[fx1][fy2] == "" || pieces_names[fx1][fy2].find(piece_color) == string::npos)
			{
				valid_moves[count_moves][0] = fx1;
				valid_moves[count_moves][1] = fy2;
				count_moves++;
			}
		}
		if (fy1 >= 0 && fy1 <= 7) //Right diagonal
		{
			if (pieces_names[fx1][fy1] == "" || pieces_names[fx1][fy1].find(piece_color) == string::npos)
			{
				valid_moves[count_moves][0] = fx1;
				valid_moves[count_moves][1] = fy1;
				count_moves++;
			}
		}
	}

	if (fx2 >= 0 && fx2 <= 7) //Lower row
	{
		if (pieces_names[fx2][source_columns] == "" || pieces_names[fx2][source_columns].find(piece_color) == string::npos)
		{
			valid_moves[count_moves][0] = fx2;
			valid_moves[count_moves][1] = source_columns;
			count_moves++;
		}
		if (fy2 >= 0 && fy2 <= 7) //Left diagonal
		{
			if (pieces_names[fx2][fy2] == "" || pieces_names[fx1][fy2].find(piece_color) == string::npos)
			{
				valid_moves[count_moves][0] = fx2;
				valid_moves[count_moves][1] = fy2;
				count_moves++;
			}
		}
		if (fy1 >= 0 && fy1 <= 7) //Right diagonal
		{
			if (pieces_names[fx2][fy1] == "" || pieces_names[fx2][fy1].find(piece_color) == string::npos)
			{
				valid_moves[count_moves][0] = fx2;
				valid_moves[count_moves][1] = fy1;
				count_moves++;
			}
		}
	}

	if (fy1 >= 0 && fy1 <= 7) //Right column
	{
		if (pieces_names[source_rows][fy1] == "" || pieces_names[source_rows][fy1].find(piece_color) == string::npos)
		{
			valid_moves[count_moves][0] = source_rows;
			valid_moves[count_moves][1] = fy1;
			count_moves++;
		}
	}

	if (fy2 >= 0 && fy2 <= 7) //Left column
	{
		if (pieces_names[source_rows][fy2] == "" || pieces_names[source_rows][fy2].find(piece_color) == string::npos)
		{
			valid_moves[count_moves][0] = source_rows;
			valid_moves[count_moves][1] = fy2;
			count_moves++;
		}
	}
}
void clearing_valid_moves()
{
	count_moves = 0;
	for (int i = 0; i < 64; i++)
	{
		valid_moves[i][0] = -1;
		valid_moves[i][1] = -1;
	}
}
bool Is_Valid_Move(int sx, int sy, int dx, int dy)
{
	bool valid = false;
	for (int i = 0; i < count_moves; i++)
	{
		if (valid_moves[i][0] == dx && valid_moves[i][1] == dy)
		{
			valid = true;
		}
	}
	return valid;
}
void move_piece(int sx, int sy, int dx, int dy, float square_size)
{
	pieces_names[dx][dy] = pieces_names[sx][sy]; //I have moved the sprite name to destination square.
	pieces_names[sx][sy] = ""; // I have remove the sprite name from source square.

	chessboard_pieces[dx][dy] = chessboard_pieces[sx][sy]; //Updated texture position in the array.
	chessboard_pieces[sx][sy].setTexture(Texture()); //Placed an empty texture

	chessboard_pieces[dx][dy].setPosition(static_cast<float>(dy) * square_size, static_cast<float>(dx) * square_size);

	clearing_valid_moves();
}
bool Is_White_In_Check(int row, int column)
{
	bool Is_check = false;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (pieces_names[i][j].find("Black") != string::npos)
			{
				clearing_valid_moves();
				if (pieces_names[i][j].find("Pawn") != string::npos)
				{
					count_moves = 0;
					pawn_capture_moves(i, j, "Black");
				}
				else if (pieces_names[i][j].find("Rook") != string::npos)
				{
					check_rook_moves(i, j, "Black");
				}
				else if (pieces_names[i][j].find("Knight") != string::npos)
				{
					check_knight_moves(i, j, "Black");
				}
				else if (pieces_names[i][j].find("Bishop") != string::npos)
				{
					check_bishop_moves(i, j, "Black");
				}
				else if (pieces_names[i][j].find("Queen") != string::npos)
				{
					check_queen_moves(i, j, "Black");
				}
				else if (pieces_names[i][j].find("King") != string::npos)
				{
					check_king_moves(i, j, "Black");
				}
				for (int k = 0; k < count_moves; k++)
				{
					if (valid_moves[k][0] == row && valid_moves[k][1] == column)
					{
						Is_check = true;
						break;
					}
				}
			}
			if (Is_check)
			{
				break;
			}
		}
		if (Is_check)
		{
			break;
		}
	}
	return Is_check;
}
bool Is_black_In_Check(int row, int column)
{
	bool Is_check = false;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (pieces_names[i][j].find("White") != string::npos)
			{
				clearing_valid_moves();
				if (pieces_names[i][j].find("Pawn") != string::npos)
				{
					count_moves = 0;
					pawn_capture_moves(i, j, "White");
				}
				else if (pieces_names[i][j].find("Rook") != string::npos)
				{
					check_rook_moves(i, j, "White");
				}
				else if (pieces_names[i][j].find("Knight") != string::npos)
				{
					check_knight_moves(i, j, "White");
				}
				else if (pieces_names[i][j].find("Bishop") != string::npos)
				{
					check_bishop_moves(i, j, "White");
				}
				else if (pieces_names[i][j].find("Queen") != string::npos)
				{
					check_queen_moves(i, j, "White");
				}
				else if (pieces_names[i][j].find("King") != string::npos)
				{
					check_king_moves(i, j, "White");
				}
				for (int k = 0; k < count_moves; k++)
				{
					if (valid_moves[k][0] == row && valid_moves[k][1] == column)
					{
						Is_check = true;
						break;
					}
				}
			}
			if (Is_check)
			{
				break;
			}
		}
		if (Is_check)
		{
			break;
		}
	}
	return Is_check;
}
bool Is_Checkmate(string current_turn)
{
	bool In_checkmate = true;
	bool inCheck;
	int king_row = -1, king_column = -1;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (pieces_names[i][j].find(current_turn + " King") != string::npos)
			{
				king_row = i;
				king_column = j;
			}
		}
	}

	if (current_turn == "White")
	{
		inCheck = Is_White_In_Check(king_row, king_column);
	}
	else
	{
		inCheck = Is_black_In_Check(king_row, king_column);
	}

	if (!inCheck)
	{
		In_checkmate = false; // if king is not in check, then checkmate will be false
	}

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (pieces_names[i][j].find(current_turn) != string::npos)
			{
				clearing_valid_moves();
				if (pieces_names[i][j].find("Pawn") != string::npos)
				{
					check_pawn_moves(i, j, current_turn);
				}
				else if (pieces_names[i][j].find("Rook") != string::npos)
				{
					check_rook_moves(i, j, current_turn);
				}
				else if (pieces_names[i][j].find("Knight") != string::npos)
				{
					check_knight_moves(i, j, current_turn);
				}
				else if (pieces_names[i][j].find("Bishop") != string::npos)
				{
					check_bishop_moves(i, j, current_turn);
				}
				else if (pieces_names[i][j].find("Queen") != string::npos)
				{
					check_queen_moves(i, j, current_turn);
				}
				else if (pieces_names[i][j].find("King") != string::npos)
				{
					check_king_moves(i, j, current_turn);
				}

				for (int k = 0; k < count_moves; k++)
				{
					int dx = valid_moves[k][0];
					int dy = valid_moves[k][1];

					string tempPiece = pieces_names[dx][dy];
					pieces_names[dx][dy] = pieces_names[i][j];
					pieces_names[i][j] = "";

					// Check if king is still in check after move
					int new_king_row = king_row;
					int new_king_col = king_column;
					if (pieces_names[dx][dy].find("King") != string::npos) {
						new_king_row = dx;
						new_king_col = dy;
					}

					bool stillInCheck;
					if (current_turn == "White")
					{
						stillInCheck = Is_White_In_Check(new_king_row, new_king_col);
					}
					else
					{
						stillInCheck = Is_black_In_Check(new_king_row, new_king_col);
					}

					pieces_names[i][j] = pieces_names[dx][dy];
					pieces_names[dx][dy] = tempPiece;

					if (!stillInCheck)
					{
						In_checkmate = false;
					}
				}
			}
		}
	}

	return In_checkmate;
}
bool Is_Stalemate(string current_turn)
{
	bool In_stalemate = true;
	bool inCheck;
	int king_row = -1, king_column = -1;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (pieces_names[i][j].find(current_turn + " King") != string::npos)
			{
				king_row = i;
				king_column = j;
			}
		}
	}

	if (current_turn == "White")
	{
		inCheck = Is_White_In_Check(king_row, king_column);
	}
	else
	{
		inCheck = Is_black_In_Check(king_row, king_column);
	}

	if (inCheck)
	{
		In_stalemate = false; // If king is in check, it cannot be stalemate
	}

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (pieces_names[i][j].find(current_turn) != string::npos)
			{
				clearing_valid_moves();
				if (pieces_names[i][j].find("Pawn") != string::npos)
				{
					check_pawn_moves(i, j, current_turn);
				}
				else if (pieces_names[i][j].find("Rook") != string::npos)
				{
					check_rook_moves(i, j, current_turn);
				}
				else if (pieces_names[i][j].find("Knight") != string::npos)
				{
					check_knight_moves(i, j, current_turn);
				}
				else if (pieces_names[i][j].find("Bishop") != string::npos)
				{
					check_bishop_moves(i, j, current_turn);
				}
				else if (pieces_names[i][j].find("Queen") != string::npos)
				{
					check_queen_moves(i, j, current_turn);
				}
				else if (pieces_names[i][j].find("King") != string::npos)
				{
					check_king_moves(i, j, current_turn);
				}

				for (int k = 0; k < count_moves; k++)
				{
					int dx = valid_moves[k][0];
					int dy = valid_moves[k][1];

					string tempPiece = pieces_names[dx][dy];
					pieces_names[dx][dy] = pieces_names[i][j];
					pieces_names[i][j] = "";

					int new_king_row = king_row;
					int new_king_col = king_column;
					if (pieces_names[dx][dy].find("King") != string::npos)
					{
						new_king_row = dx;
						new_king_col = dy;
					}

					bool stillInCheck;
					if (current_turn == "White")
					{
						stillInCheck = Is_White_In_Check(new_king_row, new_king_col);
					}
					else
					{
						stillInCheck = Is_black_In_Check(new_king_row, new_king_col);
					}

					pieces_names[i][j] = pieces_names[dx][dy];
					pieces_names[dx][dy] = tempPiece;

					if (!stillInCheck)
					{
						In_stalemate = false;
					}
				}
			}
		}
	}

	return In_stalemate;
}
void UpdateTurnText(string currentTurn)
{
	turnText.setString(currentTurn + "'s Turn");
}
void UpdateStatusText(string s)
{
	statusText.setString(s);
}
void AddCapturedPiece(string piece)
{
	if (piece.find("White") != string::npos)
	{
		blackCaptured[blackCapCount] = piece;
		blackCapCount++;
	}
	else
	{
		whiteCaptured[whiteCapCount] = piece;
		whiteCapCount++;
	}

	string whiteList = "White Captured:\n";
	for (int i = 0; i < whiteCapCount; i++)
	{
		whiteList += whiteCaptured[i] + "\n";
	}

	string blackList = "Black Captured:\n";
	for (int i = 0; i < blackCapCount; i++)
	{
		blackList += blackCaptured[i] + "\n";
	}

	whiteCapturedLabel.setString(whiteList);
	blackCapturedLabel.setString(blackList);
}
void Events_Handling(RenderWindow& window, float square_size)
{
	Event event;
	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			window.close();
		}
		if (event.type == Event::Resized)
		{
			//This part of my code will adjust the view of my window when it is resized.
			float size = max(event.size.width, event.size.height);
			FloatRect visibleArea(0, 0, size, size);
			window.setView(View(visibleArea));
		}
		if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
		{
			Vector2i pixelPos = Mouse::getPosition(window);
			Vector2f worldPos = window.mapPixelToCoords(pixelPos);
			int row = worldPos.y / square_size;
			int column = worldPos.x / square_size;
			selected_row = row;
			selected_column = column;

			cout << endl << current_turn << "'s turn" << endl;
			cout << endl << "Mouse clicked at row: " << row + 1 << ", column: " << column + 1 << endl;

			if (piece_row != -1 && piece_column != -1)
			{
				if (piece_color == current_turn)
				{
					cout << current_turn << "'s turn" << endl;
					sx = piece_row;
					sy = piece_column;
					dx = row;
					dy = column;
					int king_row = -1;
					int king_column = -1;
					bool inCheck;
					for (int i = 0; i < 8; i++)
					{
						for (int j = 0; j < 8; j++)
						{
							if (pieces_names[i][j].find(current_turn + " " + "King") != string::npos)
							{
								king_row = i;
								king_column = j;
							}
						}
					}

					int saved_count = count_moves;
					int saved_valid_moves[64][2];
					for (int z = 0; z < saved_count; ++z)  //Copying temporarily so that I can regenerate it after calling Is_Check function
					{
						saved_valid_moves[z][0] = valid_moves[z][0];
						saved_valid_moves[z][1] = valid_moves[z][1];
					}

					if (current_turn == "White")
					{
						inCheck = Is_White_In_Check(king_row, king_column);
						white_in_check = inCheck;
					}
					else
					{
						inCheck = Is_black_In_Check(king_row, king_column);
						black_in_check = inCheck;
					}

					count_moves = saved_count;
					for (int z = 0; z < saved_count; ++z) //Restoring the array back
					{
						valid_moves[z][0] = saved_valid_moves[z][0];
						valid_moves[z][1] = saved_valid_moves[z][1];
					}

					if (inCheck) //Move if source square is king
					{
						UpdateStatusText("CHECK!!");
						if (pieces_names[sx][sy].find("King") != string::npos)
						{
							if (Is_Valid_Move(sx, sy, dx, dy)) //Checking Valid move for king
							{
								if (current_turn == "White") //Switching turns
								{
									current_turn = "Black";
									UpdateTurnText(current_turn);
								}
								else
								{
									current_turn = "White";
									UpdateTurnText(current_turn);
								}

								cout << "Valid Move from (" << sx << "," << sy << ") to (" << dx << "," << dy << ")" << endl;

								if (pieces_names[dx][dy] != "")
								{
									AddCapturedPiece(pieces_names[dx][dy]);
								}
								move_piece(sx, sy, dx, dy, square_size);
								selected_row = selected_column = -1;
								piece_row = piece_column = -1;
							}
						}
					}
					else
					{
						if (Is_Valid_Move(sx, sy, dx, dy))
						{

							cout << "Valid Move from (" << sx << "," << sy << ") to (" << dx << "," << dy << ")" << endl;

							if (pieces_names[dx][dy] != "")
							{
								AddCapturedPiece(pieces_names[dx][dy]);
							}
							move_piece(sx, sy, dx, dy, square_size);
							if (pieces_names[dx][dy].find("Pawn") != string::npos)
							{
								pawn_promotion(dx, dy, piece_color);
							}

							if (current_turn == "White")
							{
								current_turn = "Black";
								UpdateTurnText(current_turn);
							}
							else
							{
								current_turn = "White";
								UpdateTurnText(current_turn);
							}

							selected_row = selected_column = -1;
							piece_row = piece_column = -1;
						}
					}
					if (Is_Checkmate(current_turn))
					{
						UpdateStatusText("CHECKMATE!");
						cout << current_turn << " is in checkmate!" << endl;
						cout << endl << current_turn << " Wins!!" << endl;
						game_over = true;
					}
					else if (Is_Stalemate(current_turn))
					{
						UpdateStatusText("STALEMATE!");
						cout << "----- Stalemate -----" << endl;
						cout << "--- Match Draw ---" << endl;
						game_over = true;
					}
				}
			}
			if (pieces_names[row][column] == "")
			{
				cout << "There is no chessboard piece on the selected square" << endl;
			}
			else
			{
				clearing_valid_moves();
				piece_row = row;
				piece_column = column;
				cout << "You clicked at piece: " << pieces_names[row][column];
				if (pieces_names[piece_row][piece_column].find("White") != string::npos)
				{
					piece_color = "White";
				}
				else
				{
					piece_color = "Black";
				}

				if (pieces_names[piece_row][piece_column].find("Pawn") != string::npos)
				{
					check_pawn_moves(piece_row, piece_column, piece_color);
				}
				else if (pieces_names[piece_row][piece_column].find("Rook") != string::npos)
				{
					check_rook_moves(piece_row, piece_column, piece_color);
				}
				else if (pieces_names[piece_row][piece_column].find("Knight") != string::npos)
				{
					check_knight_moves(piece_row, piece_column, piece_color);
				}
				else if (pieces_names[piece_row][piece_column].find("Bishop") != string::npos)
				{
					check_bishop_moves(piece_row, piece_column, piece_color);
				}
				else if (pieces_names[piece_row][piece_column].find("Queen") != string::npos)
				{
					check_queen_moves(piece_row, piece_column, piece_color);
				}
				else if (pieces_names[piece_row][piece_column].find("King") != string::npos)
				{
					check_king_moves(piece_row, piece_column, piece_color);
				}
				else
				{
					count_moves = 0;
				}

			}
		}
	}
}
void highlight_selected_square(RenderWindow& window, float square_size)
{
	if (piece_color == current_turn)
	{
		if (selected_row >= 0 && selected_column >= 0)
		{
			RectangleShape selected_square(Vector2f(square_size, square_size));
			selected_square.setPosition(static_cast<float>(selected_column) * square_size, static_cast<float>(selected_row) * square_size);
			selected_square.setFillColor(Color::Transparent);
			selected_square.setOutlineColor(Color::Blue);
			selected_square.setOutlineThickness(5.0f);
			window.draw(selected_square);
		}
	}
}
void highlight_valid_square(RenderWindow& window, float square_size)
{
	if (piece_color == current_turn)
	{
		for (int i = 0; i < count_moves; i++)
		{
			int rows = valid_moves[i][0];
			int columns = valid_moves[i][1];
			RectangleShape valid_square(Vector2f(square_size, square_size));
			valid_square.setPosition(static_cast<float>(columns) * square_size, static_cast<float>(rows) * square_size);
			valid_square.setFillColor(Color::Transparent);
			valid_square.setOutlineColor(Color::Green);
			valid_square.setOutlineThickness(5.0f);
			window.draw(valid_square);
		}
	}
}
void highlight_check_square(RenderWindow& window, float square_size, string current_turn)
{
	bool inCheck;
	int king_row = -1;
	int king_column = -1;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (pieces_names[i][j].find(current_turn + " " + "King") != string::npos)
			{
				king_row = i;
				king_column = j;
			}
		}
	}
	if (current_turn == "White")
	{
		inCheck = white_in_check;
	}
	else
	{
		inCheck = black_in_check;
	}
	if (inCheck) //Move if source square is king
	{
		if (pieces_names[sx][sy].find("King") != string::npos)
		{
			RectangleShape check_square(Vector2f(square_size, square_size));
			check_square.setPosition(static_cast<float>(king_column) * square_size, static_cast<float>(king_row) * square_size);
			check_square.setFillColor(Color::Transparent);
			check_square.setOutlineColor(Color::Red);
			check_square.setOutlineThickness(5.0f);
			window.draw(check_square);
		}
	}
}
void Initialize_Text()
{
	font.loadFromFile("Font/Inter_28pt-SemiBold.ttf");

	rightPanel.setSize(sf::Vector2f(800, 800));
	rightPanel.setPosition(800, 0);
	rightPanel.setFillColor(sf::Color(230, 230, 230));

	turnText.setFont(font);
	turnText.setCharacterSize(32);
	turnText.setFillColor(Color::Black);
	turnText.setPosition(1200, 320);
	turnText.setString("White's Turn");

	statusText.setFont(font);
	statusText.setCharacterSize(28);
	statusText.setFillColor(Color::Red);
	statusText.setPosition(1200, 370);
	statusText.setString("");

	whiteCapturedLabel.setFont(font);
	whiteCapturedLabel.setCharacterSize(24);
	whiteCapturedLabel.setFillColor(Color::Black);
	whiteCapturedLabel.setPosition(1200, 420);
	whiteCapturedLabel.setString("");

	blackCapturedLabel.setFont(font);
	blackCapturedLabel.setCharacterSize(24);
	blackCapturedLabel.setFillColor(Color::Black);
	blackCapturedLabel.setPosition(1200, 470);
	blackCapturedLabel.setString("");
}

void DrawUIPanel(sf::RenderWindow& window)
{
	window.draw(rightPanel);
	window.draw(turnText);
	window.draw(statusText);
	for (int i = 0; i < whiteCapCount; i++)
	{
		Text pieceText;
		pieceText.setFont(font);
		pieceText.setString(whiteCaptured[i]);
		pieceText.setCharacterSize(24);
		pieceText.setFillColor(sf::Color::Black);
		pieceText.setOrigin(pieceText.getLocalBounds().width / 2, pieceText.getLocalBounds().height / 2);
		pieceText.setPosition(800 + 400, 50 + i * 30); 
		window.draw(pieceText);
	}

	for (int i = 0; i < blackCapCount; i++)
	{
		Text pieceText;
		pieceText.setFont(font);
		pieceText.setString(blackCaptured[i]);
		pieceText.setCharacterSize(24);
		pieceText.setFillColor(sf::Color::Black);
		pieceText.setOrigin(pieceText.getLocalBounds().width / 2, pieceText.getLocalBounds().height / 2);
		pieceText.setPosition(800 + 400, 750 - i * 30); 
		window.draw(pieceText);
	}
}
int main()
{
	float square_size = 100;

	RenderWindow window(VideoMode(1600, 800), "Chess Game");
	window.setFramerateLimit(60);
	if (!loading_texture())
	{
		cout << "Error_loading textures" << endl;
		return -1;
	}
	if (!font.loadFromFile("Font/Inter_28pt-SemiBold.ttf"))
	{
		cout << "Error loading font!" << endl;
		return -1;
	}
	loading_texture();
	Initialize_Text();

	//Calling function of chessboard pieces.
	setting_chessboard_pieces(window, square_size);
	piece_name(window);

	while (window.isOpen() && !game_over) //Main game loop (the heart of the game)
	{
		square_size = window.getSize().x / 16.0;

		// Calling for Event_Handling function.

		Events_Handling(window, square_size);

		//clearing the window
		window.clear(Color::White);
		DrawUIPanel(window);
		//Calling chess_board function
		Chess_Board(window, square_size);

		//Calling draw_pieces function	
		draw_pieces(window, square_size);

		DrawUIPanel(window);
		//Calling highlighting functions
		highlight_selected_square(window, square_size);
		highlight_valid_square(window, square_size);
		highlight_check_square(window, square_size, current_turn);

		//Displaying my drawn window on screen
		window.display();
	}

	return 0;
}