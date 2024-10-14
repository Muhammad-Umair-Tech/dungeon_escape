#include<iostream>
#include<windows.h>
using namespace std;

char getCharAtxy(short int x, short int y); // returns the character at a location on console
void gotoxy(int x, int y); // moves the cursor to a specific location on the console
void print_maze();
void print_health_check(int x, int y);
void print_heart(int x, int y);
void print_knight();
void erase_knight();
void allow_player_to_move_knight();
void move_knight_left();
void move_knight_right();
void move_knight_up();
void move_knight_down();
void print_enemy1();
void erase_enemy1();
void move_enemy1();
void print_enemy2();
void erase_enemy2();
void move_enemy2();

void print_enemy3();
void erase_enemy3();
void move_enemy3();


int health = 100, health_check_x = 208, health_check_y = 0;
int kx = 1, ky = 1; // coordinates for knight
int e1x = 191, e1y = 1, e1_boundary_y_min = 1, e1_boundary_y_max = 22; // coordinates for enemy 1 (moves vertically) and boundaries
int e2x = 103, e2y = 50, e2_boundary_x_min = 103, e2_boundary_x_max = 191; // coordinates for enemy 2 (moves horizontally) and boundaries
bool moving_down_enemy1 = true;
bool moving_right_enemy2 = true;

int e3x = 1, e3y = 29, e3_boundary_x_min = 1, e3_boundary_x_max = 90; 
bool moving_right_enemy3 = true;

int main()
{
    int heart1_x = 2, heart1_y = 22;
    system("cls");
    print_maze();
    print_health_check(health_check_x, health_check_y);
    print_heart(heart1_x, heart1_y);
    print_knight();
    print_enemy1();
    print_enemy2();
    while(true)
    {
        allow_player_to_move_knight();
        move_enemy1();
        move_enemy2();
        move_enemy3();
    }
    return 0;
}







void allow_player_to_move_knight()
{
    if(GetAsyncKeyState(VK_UP)) // the built-in function GetAsyncKeyState() checks wether the key whose virtual key code has been passed is pressed at the time of function call or not 
        move_knight_up();
    if(GetAsyncKeyState(VK_DOWN))
        move_knight_down();
    if(GetAsyncKeyState(VK_RIGHT))
        move_knight_right();
    if(GetAsyncKeyState(VK_LEFT))
        move_knight_left();
}



void print_knight()
{
    gotoxy(kx, ky);
    cout << "^  ^^^  _^ " << endl;
    gotoxy(kx, ky + 1);
	cout << "V (' ') F> " << endl;
    gotoxy(kx, ky + 2);
	cout << " \\__|__/  " << endl;
    gotoxy(kx, ky + 3);
	cout << "    |      " << endl;
    gotoxy(kx, ky + 4);
	cout << "    |      " << endl;
    gotoxy(kx, ky + 5);
	cout << "___/ \\____" << endl;
}


void erase_knight()
{
    gotoxy(kx, ky);
    cout << "           " << endl;
    gotoxy(kx, ky + 1);
	cout << "           " << endl;
    gotoxy(kx, ky + 2);
	cout << "           " << endl;
    gotoxy(kx, ky + 3);
	cout << "           " << endl;
    gotoxy(kx, ky + 4);
	cout << "           " << endl;
    gotoxy(kx, ky + 5);
	cout << "           " << endl;
}

void print_enemy1()
{
    gotoxy(e1x, e1y);
    cout << "^  ___  __ " << endl;
    gotoxy(e1x, e1y + 1);
	cout << "V (' ') F> " << endl;
    gotoxy(e1x, e1y + 2);
	cout << " \\__|__/  " << endl;
    gotoxy(e1x, e1y + 3);
	cout << "(   |     )" << endl;
    gotoxy(e1x, e1y + 4);
	cout << "(   |     )" << endl;
    gotoxy(e1x, e1y + 5);
	cout << "___/ \\____" << endl;
}




void erase_enemy1()
{
    gotoxy(e1x, e1y);
    cout << "           " << endl;
    gotoxy(e1x, e1y + 1);
	cout << "           " << endl;
    gotoxy(e1x, e1y + 2);
	cout << "           " << endl;
    gotoxy(e1x, e1y + 3);
	cout << "           " << endl;
    gotoxy(e1x, e1y + 4);
	cout << "           " << endl;
    gotoxy(e1x, e1y + 5);
	cout << "           " << endl;
}




void move_enemy1()
{
    if(moving_down_enemy1 == true)
    {
        if(e1y < e1_boundary_y_max) // if moving_down is true, move enemy1 down
        {
            gotoxy(e1x, e1y);
            print_enemy1();
            Sleep(10);
            erase_enemy1();
            e1y++;
        }
        else
            moving_down_enemy1 = false; // if enemy1 reaches the bottom boundary, can't move down further so moving_down = false   
    }
    else if(moving_down_enemy1 == false)
    {
        if(e1y > e1_boundary_y_min) // if moving_down = false, move up
        {
            gotoxy(e1x, e1y);
            print_enemy1();
            Sleep(10);
            erase_enemy1();
            e1y--;
        }
        else 
            moving_down_enemy1 = true; // if enemy1 reaches the top boundary, can't move up further so moving_down = true  
    }     
}



void move_knight_left()
{
    if(getCharAtxy(kx - 1, ky) != '#')
    {
       
        if(getCharAtxy(kx - 1, ky) == '$')
        {
            health += 2;
            print_health_check(health_check_x, health_check_y);
        }
        erase_knight();
        kx -= 1;
        print_knight();
    }
}


void move_knight_right()
{
    
    if(getCharAtxy(kx + 11, ky) != '#') // kx + 11 because the knight is 11 points wide
    {
        if(getCharAtxy(kx + 11, ky) == '$')
        {
            health += 2;
            print_health_check(health_check_x, health_check_y);
        }
        erase_knight();
        kx += 1;
        print_knight();
    }
}


void move_knight_up()
{
    if(getCharAtxy(kx, ky - 1) == ' ' && getCharAtxy(kx, ky - 1) != '#') 
    {
        if(getCharAtxy(kx, ky - 1) == '$')
        {
            health += 2;
            print_health_check(health_check_x, health_check_y);
        } 
        erase_knight();
        ky -= 1;
        print_knight();
    }
}




void move_knight_down()
{
    if(getCharAtxy(kx, ky + 6) != '#') // ky + 6 because the knight is 6 points tall
    {
        if(getCharAtxy(kx, ky + 6) == '$')
        {
            health += 10;
            health += 2;
            print_health_check(health_check_x, health_check_y);
        }
        erase_knight();
        ky += 1;
        print_knight();
    }
}



void print_enemy2()
{
    gotoxy(e2x, e2y);
    cout << "^  ___  __ " << endl;
    gotoxy(e2x, e2y + 1);
	cout << "V (' ') F> " << endl;
    gotoxy(e2x, e2y + 2);
	cout << " \\__|__/  " << endl;
    gotoxy(e2x, e2y + 3);
	cout << "(   |     )" << endl;
    gotoxy(e2x, e2y + 4);
	cout << "(   |     )" << endl;
    gotoxy(e2x, e2y + 5);
	cout << "___/ \\____" << endl;
}




void erase_enemy2()
{
    gotoxy(e2x, e2y);
    cout << "           " << endl;
    gotoxy(e2x, e2y + 1);
	cout << "           " << endl;
    gotoxy(e2x, e2y + 2);
	cout << "           " << endl;
    gotoxy(e2x, e2y + 3);
	cout << "           " << endl;
    gotoxy(e2x, e2y + 4);
	cout << "           " << endl;
    gotoxy(e2x, e2y + 5);
	cout << "           " << endl;
}



void move_enemy2()
{
    if(moving_right_enemy2 == true)
    {
        if(e2x < e2_boundary_x_max) // if moving_down is true, move enemy1 down
        {
            gotoxy(e2x, e2y);
            print_enemy2();
            Sleep(10);
            erase_enemy2();
            e2x++;
        }
        else
            moving_right_enemy2 = false; // if enemy1 reaches the bottom boundary, can't move down further so moving_down = false   
    }
    else if(moving_right_enemy2 == false)
    {
        if(e2x > e2_boundary_x_min) // if moving_down = false, move up
        {
            gotoxy(e2x, e2y);
            print_enemy2();
            Sleep(10);
            erase_enemy2();
            e2x--;
        }
        else 
            moving_right_enemy2 = true; // if enemy1 reaches the top boundary, can't move up further so moving_down = true  
    }     
}




void print_heart(int x, int y)
{
    gotoxy(x, y);
    cout << " $$ $$ " << endl;
    gotoxy(x, y + 1);
    cout << "$  $  $" << endl;
    gotoxy(x, y + 2);
    cout << " $   $ " << endl;
    gotoxy(x, y + 3);
    cout << "  $ $  " << endl;
    gotoxy(x, y + 4);
    cout << "   $   " << endl;
}


void print_health_check(int x, int y)
{
    gotoxy(x, y);
    cout << "Health: " << health;
}



void print_maze()
{
    cout << "######################################################################################################0####################################################################################################" << endl;
    cout << "#                                                                                                     #                       #                                                                           #" << endl;
    cout << "#                                                                                                     #                       #                                                                           #" << endl;
    cout << "#                                                                                                     #                       #                                                                           #" << endl;
    cout << "#                                                                                                     #                       #                                                                           #" << endl;
    cout << "#                                                                                                     #                       #                                                                           #" << endl;
    cout << "#                                                                                                     #                       #                                                                           #" << endl;
    cout << "###########################################################################################           #           #           #                                                                           #" << endl;
    cout << "#                                                                                                     #           #           #                                                                           #" << endl;
    cout << "#                                                                                                     #           #           #                                                                           #" << endl;
    cout << "#                                                                                                     #           #           #                                                                           #" << endl;
    cout << "#                                                                                                     #           #           #                                                                           #" << endl;
    cout << "#                                                                                                     #           #           #                                                                           #" << endl;
    cout << "#                                                                                                     #           #           #                                                                           #" << endl;
    cout << "#           ###########################################################################################           #           #           #####################################################           #" << endl;
    cout << "#                                                                                                     #           #           #                                                               #           #" << endl;
    cout << "#                                                                                                     #           #           #                                                               #           #" << endl;
    cout << "#                                                                                                     #           #           #                                                               #           #" << endl;
    cout << "#                                                                                                     #           #           #                                                               #           #" << endl;
    cout << "#                                                                                                     #           #           #                                                               #           #" << endl;
    cout << "#                                                                                                     #           #           #                                                               #           #" << endl;
    cout << "###########################################################################################           #           #           #####################################################           #           #" << endl;
    cout << "#                                                                                                                 #                                                                           #           #" << endl;
    cout << "#                                                                                                                 #                                                                           #           #" << endl;
    cout << "#                                                                                                                 #                                                                           #           #" << endl;
    cout << "#                                                                                                                 #                                                                           #           #" << endl;
    cout << "#                                                                                                                 #                                                                           #           #" << endl;
    cout << "#                                                                                                                 #                                                                           #           #" << endl;
    cout << "###############################################################################################################################################################################################           #" << endl;
    cout << "#                                                                                                     #                                                                                                   #" << endl;
    cout << "#                                                                                                     #                                                                                                   #" << endl;
    cout << "#                                                                                                     #                                                                                                   #" << endl;
    cout << "#                                                                                                     #                                                                                                   #" << endl;
    cout << "#                                                                                                     #                                                                                                   #" << endl;
    cout << "#                                                                                                     #                                                                                                   #" << endl;
    cout << "#                                                                                                     #                                                                                                   #" << endl;
    cout << "#                                                                                                     #                                                                                                   #" << endl;
    cout << "#                                                                                                     #                                                                                                   #" << endl;
    cout << "#                                                                                                     #                                                                                                   #" << endl;
    cout << "#                                                                                                     #                                                                                                   #" << endl;
    cout << "#                                                                                                     #                                                                                                   #" << endl;
    cout << "#                                                                                                     #                                                                                                   #" << endl;
    cout << "#                                                                                                     #                                                                                                   #" << endl;
    cout << "#                                                                                                     #                                                                                                   #" << endl;
    cout << "#                                                                                                     #                                                                                                   #" << endl;
    cout << "#                                                                                                     #                                                                                                   #" << endl;
    cout << "#                                                                                                     #                                                                                                   #" << endl;
    cout << "#                                                                                                     #                                                                                                   #" << endl;
    cout << "#                                                                                                     #                                                                                                   #" << endl;
    cout << "#                                                                                                     #                                                                                                   #" << endl;
    cout << "#                                                                                                                                                                                                         #" << endl;
    cout << "#                                                                                                                                                                                                         #" << endl;
    cout << "#                                                                                                                                                                                                         #" << endl;
    cout << "#                                                                                                                                                                                                         #" << endl;
    cout << "#                                                                                                                                                                                                         #" << endl;
    cout << "#                                                                                                                                                                                                         #" << endl;
    cout << "######################################################################################################0####################################################################################################" << endl;
}




void gotoxy(int x, int y)
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}




char getCharAtxy(short int x, short int y)
{
    CHAR_INFO ci;
    COORD xy = {0, 0};
    SMALL_RECT rect = {x, y, x, y};
    COORD coordBufSize;
    coordBufSize.X = 1;
    coordBufSize.Y = 1;
    return ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), &ci, coordBufSize, xy, &rect) ? ci.Char.AsciiChar: ' ';
}


void move_enemy3()
{
    if(moving_right_enemy3 == true)
    {
        if(e3x < e3_boundary_x_max) // if moving_down is true, move enemy1 down
        {
            gotoxy(e3x, e3y);
            print_enemy3();
            Sleep(10);
            erase_enemy3();
            e3x++;
        }
        else
            moving_right_enemy3 = false; // if enemy1 reaches the bottom boundary, can't move down further so moving_down = false   
    }
    else if(moving_right_enemy3 == false)
    {
        if(e3x > e3_boundary_x_min) // if moving_down = false, move up
        {
            gotoxy(e3x, e3y);
            print_enemy3();
            Sleep(10);
            erase_enemy3();
            e3x--;
        }
        else 
            moving_right_enemy3 = true; // if enemy1 reaches the top boundary, can't move up further so moving_down = true  
    }     
}




void print_enemy3()
{
    gotoxy(e3x, e3y);
    cout << "^  ___  __ " << endl;
    gotoxy(e3x, e3y + 1);
	cout << "V (' ') F> " << endl;
    gotoxy(e3x, e3y + 2);
	cout << " \\__|__/  " << endl;
    gotoxy(e3x, e3y + 3);
	cout << "(   |     )" << endl;
    gotoxy(e3x, e3y + 4);
	cout << "(   |     )" << endl;
    gotoxy(e3x, e3y + 5);
	cout << "___/ \\____" << endl;
}




void erase_enemy3()
{
    gotoxy(e3x, e3y);
    cout << "           " << endl;
    gotoxy(e3x, e3y + 1);
	cout << "           " << endl;
    gotoxy(e3x, e3y + 2);
	cout << "           " << endl;
    gotoxy(e3x, e3y + 3);
	cout << "           " << endl;
    gotoxy(e3x, e3y + 4);
	cout << "           " << endl;
    gotoxy(e3x, e3y + 5);
	cout << "           " << endl;
}
