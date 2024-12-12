#include<iostream>
#include<windows.h>
#include<conio.h>
using namespace std;

char getCharAtxy(short int x, short int y); // returns the character at a location on console
void gotoxy(int x, int y); // moves the cursor to a specific location on the console
void print_maze();
void print_health_check(int x, int y);
void print_removed_health_check(int x, int y);
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
void allow_knight_to_shoot();
void allow_enemy1_to_shoot();
void allow_enemy2_to_shoot();
void allow_enemy3_to_shoot();
void hit_an_enemy_rightwards(int enemy_x, int enemy_y);
void hit_an_enemy_leftwards(int enemy_x, int enemy_y);
void open_gate_1();
void open_gate_2();
void knight_health_decrease(int bullet_x, int bullet_y);
void collision_detection(int enemy_x, int enemy_y);
void increase_score();
void victory_screen();
void defeat_screen();
string choice_screen();
void title();
void instructions();

int score = 0;
int health = 100, health_check_x = 208, health_check_y = 0;
int kx = 1, ky = 1; // coordinates for knight
int e1x = 191, e1y = 1, e1_boundary_y_min = 1, e1_boundary_y_max = 22; // coordinates for enemy 1 (moves vertically) and boundaries
int e2x = 103, e2y = 50, e2_boundary_x_min = 103, e2_boundary_x_max = 191; // coordinates for enemy 2 (moves horizontally) and boundaries
int e3x = 1, e3y = 50, e3_boundary_x_min = 1, e3_boundary_x_max = 101, e3_boundary_y_min = 50, e3_boundary_y_max = 29; // for enemy 3 (moves diagonally)
bool moving_down_enemy1 = true;
bool moving_right_enemy2 = true;
bool moving_right_enemy3 = true;
int ax_right = kx + 10, ay_right = ky + 1; // originally set to these. ax and ay are updated each time the knight moves up, down, left or right
int ax_left = kx - 4, ay_left = ky + 1;
bool shoot_right = false;
bool shoot_left = false;
int e1bx = e1x + 2, e1by = e1y + 3; // bx and by are coordinates of bullets of respective enemies
int e2bx = e2x + 4, e2by = e2y - 1;
int e3bx = e3x + 9, e3by = e3y + 3;
int enemy1_health = 100, enemy2_health = 100, enemy3_health = 100;
bool enemy1_alive = true, enemy2_alive = true, enemy3_alive = true;

int main()
{
    string choice;
    while(choice != "1")
    {
        title();
        choice = choice_screen();
        if(choice == "1")
            break;
        else if(choice == "2")
        {
            instructions();
            cout << "Press any key to continue.";
            getch();
        }
        else if(choice == "3")
            return 0;
        else
        {
            cout << "Invalid input." << endl;
            cout << "Press any key to continue.";
            getch();
        }
    }

    system("cls");
    print_maze();
    print_health_check(health_check_x, health_check_y);
    print_heart(2, 22);
    print_heart(195, 40);
    print_knight();
    while(true)
    {
        increase_score();
        allow_player_to_move_knight();
        allow_knight_to_shoot();
        knight_health_decrease(e1bx, e1by);
        knight_health_decrease(e2bx, e2by); 
        knight_health_decrease(e3bx, e3by); 
        collision_detection(e1x, e1y);
        collision_detection(e2x, e2y);
        collision_detection(e3x, e3y);
        if(enemy1_alive == true)
        {
            move_enemy1();
            allow_enemy1_to_shoot();
            if(enemy1_health == 0)
            {
                enemy1_alive = false;
                open_gate_1();
            }               
        }
        if(enemy2_alive == true)
        {
            move_enemy2();
            allow_enemy2_to_shoot();
            if(enemy2_health == 0)
            {
                enemy2_alive = false;
                open_gate_2();
            }
        }
        if(enemy3_alive == true)
        {
            move_enemy3();
            allow_enemy3_to_shoot();
            if(enemy3_health == 0)
            {
                enemy3_alive = false; 
                victory_screen();
                break;
            }
        }
        if(health == 0)
        {
            defeat_screen();
            break;
        }
        if(GetAsyncKeyState(VK_ESCAPE)) // allowing the user to exit the game by pressing the escape key
            return 0;
    }
    return 0;
}


void open_gate_1()
{
    gotoxy(191, 28);
    cout << "           ";
    gotoxy(191, 29);
    cout << "           ";
    gotoxy(191, 30);
    cout << "           ";
}


void open_gate_2()
{
    gotoxy(100, 50);
    cout << "   ";
    gotoxy(100, 51);
    cout << "   ";
    gotoxy(100, 52);
    cout << "   ";
    gotoxy(100, 53);
    cout << "   ";
    gotoxy(100, 54);
    cout << "   ";
    gotoxy(100, 55);
    cout << "   ";
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
    if(kx >= 103 && ky < 29) // changing colours
        system("Color 90");
    else if(kx < 103 && ky < 29)   
        system("Color A0");
    else if(kx >= 103 && ky >= 29)
        system("Color E0");
    else if(kx < 103 && ky >= 29)
        system("Color B0"); 
}



void print_knight()
{
    gotoxy(kx, ky);
    cout << "   ^^^  _  " << endl;
    gotoxy(kx, ky + 1);
	cout << "Z (' ') F> " << endl;
    gotoxy(kx, ky + 2);
	cout << " \\__|__/  " << endl;
    gotoxy(kx, ky + 3);
	cout << "    |      " << endl;
    gotoxy(kx, ky + 4);
	cout << "    |      " << endl;
    gotoxy(kx, ky + 5);
	cout << "   / \\    " << endl;
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




void move_knight_left()
{   // chcking if there's no wall on the knight's left for its entire height (6 points on y-axis)
    if((getCharAtxy(kx - 1, ky) != '#') && (getCharAtxy(kx - 1, ky + 1) != '#') && (getCharAtxy(kx - 1, ky + 2) != '#') && (getCharAtxy(kx - 1, ky + 3) != '#') && (getCharAtxy(kx - 1, ky + 4) != '#') && (getCharAtxy(kx - 1, ky + 5) != '#'))
    {
        if(getCharAtxy(kx - 1, ky) == '$')
        {
            health += 2;
            score += 2;
            print_health_check(health_check_x, health_check_y);
        }
        erase_knight();
        kx -= 1;
        Sleep(10);
        print_knight();
        ax_right -= 1;
        ax_left -= 1;
    }
}


void move_knight_right()
{
    // kx + 11 because the knight is 11 points wide
    // chcking if there's no wall on the knight's right for its entire height (6 points on y-axis)
    if((getCharAtxy(kx + 11, ky) != '#') && (getCharAtxy(kx + 11, ky + 1) != '#') && (getCharAtxy(kx + 11, ky + 2) != '#') && (getCharAtxy(kx + 11, ky + 3) != '#') && (getCharAtxy(kx + 11, ky + 4) != '#') && (getCharAtxy(kx + 11, ky + 5) != '#'))
    {
        if(getCharAtxy(kx + 11, ky) == '$')
        {
            health += 2;
            score += 2;
            print_health_check(health_check_x, health_check_y);
        }
        erase_knight();
        kx += 1;
        Sleep(10);
        print_knight();
        ax_right += 1;
        ax_left += 1;
    }
}


void move_knight_up()
{   // checking if there's only empty space above knight for its entire width (11 on x-axis)
    if((getCharAtxy(kx, ky - 1) == ' ' && getCharAtxy(kx, ky - 1) != '#') && (getCharAtxy(kx + 1, ky - 1) == ' ' && getCharAtxy(kx + 1, ky - 1) != '#') && (getCharAtxy(kx + 2, ky - 1) == ' ' && getCharAtxy(kx + 2, ky - 1) != '#') && (getCharAtxy(kx + 3, ky - 1) == ' ' && getCharAtxy(kx + 3, ky - 1) != '#') && (getCharAtxy(kx + 4, ky - 1) == ' ' && getCharAtxy(kx + 4, ky - 1) != '#') && (getCharAtxy(kx + 5, ky - 1) == ' ' && getCharAtxy(kx + 5, ky - 1) != '#') && (getCharAtxy(kx + 6, ky - 1) == ' ' && getCharAtxy(kx + 6, ky - 1) != '#') && (getCharAtxy(kx + 7, ky - 1) == ' ' && getCharAtxy(kx + 7, ky - 1) != '#') && (getCharAtxy(kx + 8, ky - 1) == ' ' && getCharAtxy(kx + 8, ky - 1) != '#') && (getCharAtxy(kx + 9, ky - 1) == ' ' && getCharAtxy(kx + 9, ky - 1) != '#') && (getCharAtxy(kx + 10, ky - 1) == ' ' && getCharAtxy(kx + 10, ky - 1) != '#')) 
    {
        if(getCharAtxy(kx, ky - 1) == '$')
        {
            health += 2;
            score += 2;
            print_health_check(health_check_x, health_check_y);
        } 
        erase_knight();
        ky -= 1;
        Sleep(10);
        print_knight();
        ay_right -= 1;
        ay_left -= 1;
    }
}




void move_knight_down()
{   // ky + 6 because the knight is 6 points tall
    // checking if there's only empty space below knight for its entire width (11 on x-axis)
    if((getCharAtxy(kx, ky + 6) != '#') && (getCharAtxy(kx + 1, ky + 6) != '#') && (getCharAtxy(kx + 2, ky + 6) != '#') && (getCharAtxy(kx + 3, ky + 6) != '#') && (getCharAtxy(kx + 4, ky + 6) != '#') && (getCharAtxy(kx + 5, ky + 6) != '#') && (getCharAtxy(kx + 6, ky + 6) != '#') && (getCharAtxy(kx + 7, ky + 6) != '#') && (getCharAtxy(kx + 8, ky + 6) != '#') && (getCharAtxy(kx + 9, ky + 6) != '#') && (getCharAtxy(kx + 10, ky + 6) != '#')) 
    {
        if(getCharAtxy(kx, ky + 6) == '$')
        {
            health += 10;
            health += 2;
            score += 2;
            print_health_check(health_check_x, health_check_y);
        }
        erase_knight();
        ky += 1;
        Sleep(10);
        print_knight();
        ay_right += 1;
        ay_left += 1;
    }
}


void print_enemy1()
{
    gotoxy(e1x, e1y);
    cout << "     ^     " << endl;
    gotoxy(e1x, e1y + 1);
	cout << "  <(\\./)> " << endl;
    gotoxy(e1x, e1y + 2);
	cout << "     @     " << endl;
    gotoxy(e1x, e1y + 3);
	cout << "  <==@     " << endl;
    gotoxy(e1x, e1y + 4);
	cout << "     @     " << endl;
    gotoxy(e1x, e1y + 5);
	cout << "    / \\   " << endl;
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
    if(enemy1_health == 0)
    {
        erase_enemy1();
        e1x = -1;
        e1y = -1;
        enemy1_alive = false;
        return;
    }
    if(moving_down_enemy1 == true)
    {
        if(e1y < e1_boundary_y_max) // if moving_down is true, move enemy1 down
        {
            gotoxy(e1x, e1y);
            print_enemy1();
            Sleep(10);
            erase_enemy1();
            e1y++;
            e1by++;
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
            e1by--;
        }
        else 
            moving_down_enemy1 = true; // if enemy1 reaches the top boundary, can't move up further so moving_down = true  
    }     
}


void print_enemy2()
{
    gotoxy(e2x, e2y);
    cout << "   MMM     " << endl;
    gotoxy(e2x, e2y + 1);
	cout << "  (\\./)   " << endl;
    gotoxy(e2x, e2y + 2);
	cout << "^   @   ^  " << endl;
    gotoxy(e2x, e2y + 3);
	cout << "||==@==|| " << endl;
    gotoxy(e2x, e2y + 4);
	cout << "    @     " << endl;
    gotoxy(e2x, e2y + 5);
	cout << "   / \\   " << endl;
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
    if(enemy2_health == 0)
    {
        erase_enemy2();
        e2x = -1;
        e2y = -1;
        enemy2_alive = false;
        return;
    }    
    if(moving_right_enemy2 == true)
    {
        if(e2x < e2_boundary_x_max) // if moving_down is true, move enemy1 down
        {
            gotoxy(e2x, e2y);
            print_enemy2();
            Sleep(10);
            erase_enemy2();
            e2x++;
            e2bx++;
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
            e2bx--;
        }
        else 
            moving_right_enemy2 = true; // if enemy1 reaches the top boundary, can't move up further so moving_down = true  
    }     
}


void print_enemy3()
{
    gotoxy(e3x, e3y);
    cout << " ||||||||| " << endl;
    gotoxy(e3x, e3y + 1);
	cout << " !!(\\./)!!" << endl;
    gotoxy(e3x, e3y + 2);
	cout << "     @     " << endl;
    gotoxy(e3x, e3y + 3);
	cout << "     @==>  " << endl;
    gotoxy(e3x, e3y + 4);
	cout << "     @     " << endl;
    gotoxy(e3x, e3y + 5);
	cout << "    / \\   " << endl;
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



void move_enemy3()
{
    if(enemy3_health == 0)
    {
        erase_enemy3();
        e3x = -1;
        e3y = -1;
        enemy3_alive = false;
        return;
    }    
    if(moving_right_enemy3 == true)
    {
        if(e3x < e3_boundary_x_max && e3y > e3_boundary_y_max) // if moving_down is true, move enemy1 down
        {
            gotoxy(e3x, e3y);
            print_enemy3();
            Sleep(10);
            erase_enemy3();
            e3x++;
            e3y--;
            e3bx++;
            e3by--;
        }
        else
            moving_right_enemy3 = false; // if enemy1 reaches the bottom boundary, can't move down further so moving_down = false   
    }
    else if(moving_right_enemy3 == false)
    {
        if(e3x > e3_boundary_x_min && e3y < e3_boundary_y_min) // if moving_down = false, move up
        {
            gotoxy(e3x, e3y);
            print_enemy3();
            Sleep(10);
            erase_enemy3();
            e3x--;
            e3y++; // bullet cannot go backwards, so no e3bx--
            e3by++;
        }
        else 
            moving_right_enemy3 = true; // if enemy1 reaches the top boundary, can't move up further so moving_down = true  
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


void remove_heart(int x, int y)
{
    gotoxy(x, y);
    cout << "       " << endl;
    gotoxy(x, y + 1);
    cout << "       " << endl;
    gotoxy(x, y + 2);
    cout << "       " << endl;
    gotoxy(x, y + 3);
    cout << "       " << endl;
    gotoxy(x, y + 4);
    cout << "       " << endl;
}



void print_health_check(int x, int y)
{
    gotoxy(x, y);
    cout << "Score: " << score;
    gotoxy(x, y + 1);
    cout << "Health: " << health;
    gotoxy(x, y + 2);
    cout << "Enemy 1 health: " << enemy1_health;
    gotoxy(x, y + 3);
    cout << "Enemy 2 health: " << enemy2_health;
    gotoxy(x, y + 4);
    cout << "Enemy 3 health: " << enemy3_health;
}


void print_removed_health_check(int x, int y)
{
    gotoxy(x, y);
    cout << "                   ";
    gotoxy(x, y + 1);
    cout << "                   ";
    gotoxy(x, y + 2);
    cout << "                   ";
    gotoxy(x, y + 3);
    cout << "                   ";
    gotoxy(x, y + 4);
    cout << "                   ";
}


void allow_knight_to_shoot()
{ 
    if(GetAsyncKeyState(68)) // shooting rightwards (ascii for D is 68)
        shoot_right = true;
    if(shoot_right == true)
    {   // checking if there's no wall of # infront of the arrow
        if((getCharAtxy(ax_right, ay_right) != '#') && (getCharAtxy(ax_right + 1, ay_right) != '#') && (getCharAtxy(ax_right + 2, ay_right) != '#') && (getCharAtxy(ax_right + 3, ay_right) != '#') && (getCharAtxy(ax_right + 4, ay_right) != '#'))
        {
            gotoxy(ax_right, ay_right);
            cout << "--->";
            Sleep(10);
            gotoxy(ax_right, ay_right);
            cout << "    ";
            ax_right += 4;
        }
        else
        {
            shoot_right = false;
            ax_right = kx + 10;
            ay_right = ky + 1;
        }
        

        // CHANGE
        if(enemy1_alive == true)
            hit_an_enemy_rightwards(e1x, e1y); // check for collision with enemy 1 using rightwards arrow
        if(enemy2_alive == true)
            hit_an_enemy_rightwards(e2x, e2y); // check for collision with enemy 2 using rightwards arrow 
        if(enemy3_alive == true)
            hit_an_enemy_rightwards(e3x, e3y); // check for collision with enemy 3 using rightwards arrow 
    }

    if(GetAsyncKeyState(65)) // shooting leftwards (ascii for A is 65)
        shoot_left = true;
    if(shoot_left == true)
    {   // checking if there's no wall of # infront of the arrow
        if((getCharAtxy(ax_left + 4, ay_left) != '#') && (getCharAtxy(ax_left + 3, ay_left) != '#') && (getCharAtxy(ax_left + 2, ay_left) != '#') && (getCharAtxy(ax_left + 1, ay_left) != '#') && (getCharAtxy(ax_left, ay_left) != '#'))
        {
            gotoxy(ax_left, ay_left);
            cout << "<---";
            Sleep(10);
            gotoxy(ax_left, ay_left);
            cout << "    ";
            ax_left -= 4;
        }
        else
        {
            shoot_left = false;
            ax_left = kx - 4;
            ay_left = ky + 1;
        }



        if(enemy2_alive == true)
            hit_an_enemy_leftwards(e2x, e2y);
        if(enemy3_alive == true)
            hit_an_enemy_leftwards(e3x, e3y);
    }    
}


void allow_enemy1_to_shoot()
{   
    if(enemy1_health != 0)
    {
        if(getCharAtxy(e1bx - 1, e1by + 1) != '#')
        {
            gotoxy(e1bx, e1by);
            cout << "O";
            Sleep(10);
            gotoxy(e1bx, e1by);
            cout << " ";
            e1bx -= 1;
        }
        else
        {
            e1bx = e1x + 2;
            e1by = e1y + 3;
        }
    }
    else
    {
        e1bx = -1;
        e1by = -1;
    }
}


void allow_enemy2_to_shoot()
{
    if(enemy2_health != 0)
    {
        if(getCharAtxy(e2bx, e2by) != '#')
        {
            gotoxy(e2bx, e2by);
            cout << "O";
            Sleep(10);
            gotoxy(e2bx, e2by);
            cout << " ";
            e2by--;
        }
        else
        {
            e2bx = e2x + 4;
            e2by = e2y - 1;
        }
    }
    else
    {
        e2bx = -1;
        e2by = -1;
    }
}



void allow_enemy3_to_shoot()
{
    if(enemy3_health != 0)
    {
        if(getCharAtxy(e3bx, e3by) != '#')
        {
            gotoxy(e3bx, e3by);
            cout << "O";
            Sleep(10);
            gotoxy(e3bx, e3by);
            cout << " ";
            e3bx++;
        }
        else
        {
            e3bx = e3x + 9;
            e3by = e3y + 3;
        }
    }
    else
    {
        e3bx = -1;
        e3by = -1;
    }
}




void hit_an_enemy_rightwards(int enemy_x, int enemy_y)
{
    if((ax_right > enemy_x && ax_right <= enemy_x + 11) && (ay_right > enemy_y && ay_right <= enemy_y + 6))
    {
        if(enemy_x == e1x)
        {
            enemy1_health -= 10;
            score += 10;
        }
        else if(enemy_x == e2x)
        {
            enemy2_health -= 10;
            score += 10;
        }
        else if(enemy_x == e3x)
        {
            enemy3_health -= 10;
            score += 10;
        }
        shoot_right = false;
        ax_right = kx + 10;
        ay_right = ky + 1;
        print_removed_health_check(health_check_x, health_check_y);
        print_health_check(health_check_x, health_check_y);
    }
}


void hit_an_enemy_leftwards(int enemy_x, int enemy_y)
{
    if((ax_left > enemy_x && ax_left <= enemy_x + 11) && (ay_left > enemy_y && ay_left <= enemy_y + 6))
    {
        if(enemy_x == e2x)
        {
            enemy2_health -= 10;
            score += 10;
        }
        else if(enemy_x == e3x)
        {
            enemy3_health -= 10;
            score += 10;
        }
        shoot_left = false;
        ax_left = kx - 4;
        ay_left = ky + 1;
        print_removed_health_check(health_check_x, health_check_y);
        print_health_check(health_check_x, health_check_y);
    }
}


void knight_health_decrease(int bullet_x, int bullet_y)
{
    if((bullet_x > kx && bullet_x <= kx + 11) && (bullet_y > ky && bullet_y <= ky + 6))
    {
        health -= 5;
        print_removed_health_check(health_check_x, health_check_y);
        print_health_check(health_check_x, health_check_y);
    }
}


void increase_score()
{
    score++;
    print_removed_health_check(health_check_x, health_check_y);
    print_health_check(health_check_x, health_check_y);
}


void collision_detection(int enemy_x, int enemy_y)
{
    if((kx <= enemy_x + 11 && kx + 11 >= enemy_x) && (ky <= enemy_y + 6 && ky + 6 >= enemy_y))
    {
        health = 0;
    }
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
    cout << "###########################################################################################################################################################################################################" << endl;
    cout << "#                                                                                                     #                                                                                        VVVVVVVVVVV#" << endl;
    cout << "#                                                                                                     #                                                                                        ############" << endl;
    cout << "#                                                                                                     #                                                                                                   #" << endl;
    cout << "#                                                                                                     #                                                                                                   #" << endl;
    cout << "#                                                                                                     #                                                                                                   #" << endl;
    cout << "#                                                                                                     #                                                                                                   #" << endl;
    cout << "#                                                                                                     #                                                                                                   #" << endl;
    cout << "#                                                                                                     #                                                                                                   #" << endl;
    cout << "#                                                                                                     #                                                                                                   #" << endl;
    cout << "#                                                                                                     #                                                                                                   #" << endl;
    cout << "#                                                                                                     #           #########################################################################################" << endl;
    cout << "#                                                                                                     #                                     #                              #                              #" << endl;
    cout << "#                                                                                                     #                                     #                              #                              #" << endl;
    cout << "#                                                                                                     #                                     #                              #                              #" << endl;
    cout << "#                                                                                                     #                                     #                              #                              #" << endl;
    cout << "#                                                                                                     #                                     #                              #                              #" << endl;
    cout << "#                                                                                                     #                                     #                              #                              #" << endl;
    cout << "#                                                                                                     #                                     #                              #                              #" << endl;
    cout << "#                                                                                                     #                                     #                              #                              #" << endl;
    cout << "#                                                                                                     #                                     #                              #                              #" << endl;
    cout << "#                                                                                                     #                                     #                              #                       ########" << endl;
    cout << "#                                                                                                   #<#                                                                                                   #" << endl;
    cout << "#                                                                                                   #<#                                                                                                   #" << endl;
    cout << "#                                                                                                   #<#                                                                                                   #" << endl;
    cout << "#                                                                                                   #<#                                                                                                   #" << endl;
    cout << "#                                                                                                   #<#                                                                                                   #" << endl;
    cout << "#                                                                                                   #<#                                                                                                   #" << endl;
    cout << "######################################################################################################0####################################################################################################" << endl;
}


void victory_screen()
{
    system("cls");
    system("Color 60");
    cout << endl << endl;
    cout << "    ####### #      # #######        ######    #      # #######   ######  #######       #######  ######          ######  ######  #       #  ######  #       ####### ####### ####### |    " << endl;
    cout << "       #    #      # #             #      #   #      # #       ##      #    #             #    ##     #        #       #      # ##     ## #      # #       #          #    #       |    " << endl;
    cout << "       #    ######## ######        #      #   #      # ######    ##         #             #      ##            #       #      # # #   # # #######  #       ######     #    ######  |    " << endl;
    cout << "       #    #      # #             #      #   #      # #           ##       #             #        ##          #       #      # #  # #  # #        #       #          #    #       |    " << endl;
    cout << "       #    #      # #             #     #### #      # #       #     ##     #             #    #     ##        #       #      # #   #   # #        #       #          #    #       |    " << endl;
    cout << "       #    #      # #######        ######  #  ######  #######  ######      #          #######  ######          ######  ######  #       # #        ####### #######    #    ####### O    " << endl;
    cout << endl << endl << "Your score: " << score << endl;
}


void defeat_screen()
{
    system("cls");
    system("Color 47");
    cout << endl << endl;
    cout << "    ####### #      # #######       #  #  #    # ####### ####### #      # #######        #      # #######  ######         ####### ####### #       #       ####### #    # |    " << endl;
    cout << "       #    #      # #             # #   ##   #    #    #       #      #    #           #      # #     # ##     #        #       #     # #       #       #       ##   # |    " << endl;
    cout << "       #    ######## ######        ##    # #  #    #    #       ########    #           ######## #######   ##            ######  ####### #       #       ######  # #  # |    " << endl;
    cout << "       #    #      # #             # #   #  # #    #    #   ### #      #    #           #      # #     #     ##          #       #     # #       #       #       #  # # |    " << endl;
    cout << "       #    #      # #             #  #  #   ##    #    #     # #      #    #           #      # #     # #     ##        #       #     # #       #       #       #   ## |    " << endl;
    cout << "       #    #      # #######       #   # #    #  ###### ####### #      #    #           #      # #     #  ######         #       #     # ####### ####### ####### #    # O    " << endl;
    cout << endl << endl << "Your score: " << score << endl;
}


void title()
{
    system("cls");
    system("Color 7C");
    cout << endl << endl << endl;
    cout << "\t\t\t\t\t _____________________________________________________________________________________________________________________________________________" << endl;
    cout << "\t\t\t\t\t|                                                                                                                                             |" << endl;
    cout << "\t\t\t\t\t|  #################   ##             ##  ####           ##  #################    #################  ###################   ####           ##  |" << endl;
    cout << "\t\t\t\t\t|  #################   ##             ##  #####          ##  #################    #################  ###################   #####          ##  |" << endl;
    cout << "\t\t\t\t\t|  ##              ##  ##             ##  ##  ##         ##  ##             ##    ##                 ##               ##   ##  ##         ##  |" << endl;
    cout << "\t\t\t\t\t|  ##              ##  ##             ##  ##   ##        ##  ##             ##    ##                 ##               ##   ##   ##        ##  |" << endl;
    cout << "\t\t\t\t\t|  ##              ##  ##             ##  ##    ##       ##  ##                   ##                 ##               ##   ##    ##       ##  |" << endl;
    cout << "\t\t\t\t\t|  ##              ##  ##             ##  ##     ##      ##  ##                   ###############    ##               ##   ##     ##      ##  |" << endl;
    cout << "\t\t\t\t\t|  ##              ##  ##             ##  ##      ##     ##  ##                   ###############    ##               ##   ##      ##     ##  |" << endl;
    cout << "\t\t\t\t\t|  ##              ##  ##             ##  ##       ##    ##  ##                   ##                 ##               ##   ##       ##    ##  |" << endl;
    cout << "\t\t\t\t\t|  ##              ##  ##             ##  ##        ##   ##  ##           ######  ##                 ##               ##   ##        ##   ##  |" << endl;
    cout << "\t\t\t\t\t|  ##              ##  ##             ##  ##         ##  ##  ##           ######  ##                 ##               ##   ##         ##  ##  |" << endl;
    cout << "\t\t\t\t\t|  ##              ##  ##             ##  ##          ## ##  ##             ##    ##                 ##               ##   ##          ## ##  |" << endl;
    cout << "\t\t\t\t\t|  #################   #################  ##           ####  #################    #################  ###################   ##           ####  |" << endl;
    cout << "\t\t\t\t\t|  #################   #################  ##            ###  #################    #################  ###################   ##            ###  |" << endl;
    cout << "\t\t\t\t\t|                                                                                                                                             |" << endl;
    cout << "\t\t\t\t\t|               #################   ###############   #################   ###############   #################   #################             |" << endl;
    cout << "\t\t\t\t\t|               #################   ###############   #################   ###############   #################   #################             |" << endl;
    cout << "\t\t\t\t\t|               ##                 ##                ##                  ##             ##  ##              ##  ##                            |" << endl;
    cout << "\t\t\t\t\t|               ##                 ###               ##                  ##             ##  ##              ##  ##                            |" << endl;
    cout << "\t\t\t\t\t|               ##                    ##             ##                  ##             ##  ##              ##  ##                            |" << endl;
    cout << "\t\t\t\t\t|               ###############       ###            ##                  #################  #################   ###############               |" << endl;
    cout << "\t\t\t\t\t|               ###############          ##          ##                  #################  #################   ###############               |" << endl;
    cout << "\t\t\t\t\t|               ##                       ###         ##                  ##             ##  ##                  ##                            |" << endl;
    cout << "\t\t\t\t\t|               ##                          ##       ##                  ##             ##  ##                  ##                            |" << endl;
    cout << "\t\t\t\t\t|               ##                          ###      ##                  ##             ##  ##                  ##                            |" << endl;
    cout << "\t\t\t\t\t|               ##                             ##    ##                  ##             ##  ##                  ##                            |" << endl;
    cout << "\t\t\t\t\t|               #################  ###############    #################  ##             ##  ##                  #################             |" << endl;
    cout << "\t\t\t\t\t|               #################  ###############    #################  ##             ##  ##                  #################             |" << endl;
    cout << "\t\t\t\t\t|_____________________________________________________________________________________________________________________________________________|" << endl;
    cout << endl << endl << endl;
}


string choice_screen()
{
    string choice;
    cout << "1. Start the Quest" << endl;
    cout << "2. Read the Scrolls" << endl;
    cout << "3. Flee the Dungeon" << endl;
    cout << "Choice: ";
    getline(cin, choice);
    return choice;
}



void instructions()
{
    cout << endl << endl << endl << endl;
    cout << "THE QUEST: " << endl << endl;
    cout << "\tYour goal is to navigate the treacherous dungeon, defeat enemies, and escape through the final gate. Beware of traps, falling health, and relentless foes. Only the bravest will survive!" << endl << endl << endl << endl;
    cout << "CONTROLS: " << endl << endl;
    cout << "\t--> Arrow keys: Move your knight." << endl;
    cout << "\t\t--> Up Arrow: Move up." << endl;
    cout << "\t\t--> Down Arrow: Move down." << endl;
    cout << "\t\t--> Left Arrow: Move left." << endl;
    cout << "\t\t--> Right Arrow: Move right." << endl;
    cout << "\t--> A: Fire an arrow to the left." << endl;
    cout << "\t--> D: FIre an arrow to the right." << endl << endl << endl << endl;
    cout << "GAMEPLAY: " << endl << endl;
    cout << "\tWatch Your Health: " << endl;
    cout << "\t\t--> Your health starts at 100. If it reaches 0, you lose the game." << endl;
    cout << "\t\t--> Collect Hearts to regain health." << endl;
    cout << "\tDefeat the Enemies: " << endl;
    cout << "\t\t--> Use the A and D keys to attack enemies. Aim carefully!" << endl;
    cout << "\t\t--> Each enemy has its own movement pattern. Learn them to avoid damage." << endl;
    cout << "\tAvoid Bullets: " << endl;
    cout << "\t\t--> Enemies fire bullets that can decrease your health. Stay sharp and dodge!" << endl;
    cout << "\tUnlock Gates: " << endl;
    cout << "\t\t--> Defeating specific enemies will unlock gates. Keep an eye on your surroundings." << endl;
    cout << "\tDefeat all the enemies and escape through the final gate to achieve victory! Remember, strategy and precision are key to survival." << endl;
    cout << "\tIf your health drops to 0, or if you get too close enemy, the dungeon claims another soul. Better luck next time!" << endl << endl << endl << endl;
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
