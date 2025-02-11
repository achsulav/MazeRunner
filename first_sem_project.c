
#include <graphics.h>//For graphic Feature
#include <stdlib.h>//Memory Allocation
#include <conio.h>//Using feature like getch
#include <time.h>//For Time Feature
#include <stdio.h>//Standard Input & Output
#include <dos.h>//Using Delay Feature
#define maxlevel 3

struct Player {
    char name[50];
    int score;
};
//All the functions
void maze(int x, int y, int levels);//Generate a maze w.r.t level
void displayLeaderboard(struct Player leaderboard[], int playerCount);//Simply display player leaderboard
void updateLeaderboard(struct Player leaderboard[], int playerCount, struct Player newPlayer);//Display new player leaderboard
void playGame(int levels, struct Player* player);//Run the game w.r.t levels, player = player all info
void Timer(int startTime, int duration);//Timer w.r.t each different level have different duration

int main() {
int gdriver = DETECT, gmode;
initgraph(&gdriver, &gmode, "C:\\TurboC3\\BGI");
struct Player leaderboard[100];
int playerCount = 0;
char choice;

do {
cleardevice();
outtextxy(100, 100, "Maze Game");
outtextxy(100, 130, "1. Play Game");
outtextxy(100, 160, "2. Leaderboard");
outtextxy(100, 190, "3. Exit");
choice = getch();

switch (choice) {
case '1': {
cleardevice();
struct Player player;
outtextxy(100, 100, "Enter your name: ");
scanf("%s", player.name);
outtextxy(100, 130, "Select Levels");
outtextxy(100, 160, "1. Easy");
outtextxy(100, 190, "2. Normal");
outtextxy(100, 220, "3. Hard");

int levels = getch() - '0';

cleardevice();
playGame(levels, &player);

updateLeaderboard(leaderboard, playerCount, player);
playerCount++;
break;
   }
case '2':
cleardevice();
displayLeaderboard(leaderboard, playerCount);
getch();
break;



case '3':
closegraph();
exit(0);
default:
break;

       }
    } while (choice != '3');

    closegraph();
    return 0;
}

void playGame(int levels, struct Player* player) {
for (int level = 1; level <= maxlevel; ++level) {
int x = 100, y = 0;
char ch = 0;
maze(x, y, levels);

int duration = levels * 30; // Level Easy=30s, Normal=60s, Hard=90s
int startTime = time(0);

int levelCompleted = 0;
//ASCII Code for ESC KEY
while (ch != 27) {
//Timer
Timer(startTime, duration);
int timeRemaining = duration - (time(0) - startTime);
if (timeRemaining <= 0) {
outtextxy(250, 250, "Time Finish");
getch();
return;
}
//kbhit means check key is press
if (kbhit()) {
ch = getch();
int newX = x, newY = y;
switch (ch) {
case 72: // Up arrow key
newY -= 10;
break;
case 80: // Down arrow key
newY += 10;
break;
case 77: // Right arrow key
newX += 10;
break;
case 75: // Left arrow key
newX -= 10;
break;
}

if (getpixel(newX, newY) != 3) {
setcolor(BLACK);
circle(x, y, 3);



x = newX;
y = newY;

setcolor(YELLOW);
circle(x, y, 3); // Draw the new position
setfillstyle(1, 2);

}

if (x == 310) {
 outtextxy(350, 200, "Level Completed");
(*player).score += 1000; // Example score increment per level
levelCompleted = 1;
delay(5000); // Pause before next level
break;
}
  }
    }
if (!levelCompleted) {
outtextxy(250, 250, "Game Over");
getch();
break;
}
levels++; // Increase difficulty for next level
    }
    outtextxy(250, 250, "Press any key to exit");
    getch();
}

//Generating random maze passing in line function
void maze(int x, int y, int levels) {
    setcolor(3);
    switch (levels) {
case 1: // Easy
   for (int i = 0; i < 10; i++) {
for (int j = 0; j < 10; j++) {
   int spacing = 40;
   x = i* spacing;
   y = j*spacing;

   if (rand() % 2 == 0) {
line(x,y+spacing, x,y); //
   } else {
line(y,x,y+spacing,x); //
   }
}
   }
   rectangle(0,0,400,400);
   break;
case 2: // Normal;
int spacing = 40;
    int x, y;

    for ( i = 0; i < 10; i++) {
for (int j = 0; j < 10; j++) {
   x = i * spacing;
   y = j * spacing;

   if (rand() % 2 == 0) {
line(x, y + spacing, x + spacing, y); // Draw diagonal line from bottom-left to top-right
   } else {
line(x + spacing, y + spacing, x, y); // Draw diagonal line from bottom-right to top-left
   }
}
    }

    rectangle(0, 0, 400, 400); // Draw outer rectangle


   break;
case 3: // Hard
cleardevice();
int space=40;
      x,y;

    for ( i = 0; i < 10; i++) {
for (int j = 0; j < 10; j++) {
   x=i* space;
   y=j * space;

   if (rand() % 2 == 0) {
line(x,y+ space, x + space, y);// Draw diagonal line from bottom-left to top-right
   } else {
line(x+ space, y+ space, x,y);// Draw diagonal line from bottom-right to top-left
   }
}
    }

    rectangle(0, 0, 400, 400); // Draw outer rectangle


   break;
    }

    setcolor(WHITE);
    outtextxy(65, 15, "Entry");
    outtextxy(315, 297, "Exit");
    setcolor(YELLOW);
    circle(x, y, 3);
    setfillstyle(1, 2);
    floodfill(x, y, 14);
}

void displayLeaderboard(struct Player leaderboard[], int playerCount) {
    outtextxy(100, 100, "Leaderboard:");
    for (int i = 0; i < playerCount; i++) {
        char scoreText[100];
        sprintf(scoreText, "%d. %s - %d", i + 1, leaderboard[i].name, leaderboard[i].score);
        outtextxy(100, 130 + (i * 30), scoreText);
    }
}

void updateLeaderboard(struct Player leaderboard[], int playerCount, struct Player newPlayer) {
    leaderboard[playerCount] = newPlayer;
    // Sort leaderboard by score (simple bubble sort for demonstration)
    for (int i = 0; i < playerCount; i++) {
        for (int j = 0; j < playerCount - i; j++) {
            if (leaderboard[j].score < leaderboard[j + 1].score) {
                struct Player temp = leaderboard[j];
                leaderboard[j] = leaderboard[j + 1];
                leaderboard[j + 1] = temp;
            }
        }
    }
}

void Timer(int startTime, int duration) {
    int timeRemaining = duration - (time(0) - startTime);
    char timerText[50];
    sprintf(timerText, "Time Left: %d seconds", timeRemaining);
    setcolor(WHITE);
    outtextxy(400, 20, timerText);
}
Error Icon
Address not found
Your message wasn't delivered to gangadharshsh12@gmail.com because the address couldn't be found, or is unable to receive mail.
LEARN MORE
The response was:
550 5.1.1 The email account that you tried to reach does not exist. Please try double-checking the recipient's email address for typos or unnecessary spaces. For more information, go to https://support.google.com/mail/?p=NoSuchUser a1e0cc1a2514c-85b0f6ca41asor132593241.1 - gsmtp




---------- Forwarded message ----------
From: "Sûlãv Āçhåryâ" <mrsulav8@gmail.com>
To: gangadharshsh12@gmail.com
Cc: 
Bcc: 
Date: Fri, 22 Nov 2024 09:12:02 -1200
Subject: Maze Game
----- Message truncated -----
