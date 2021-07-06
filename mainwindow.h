#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPixmap>
#include <QKeyEvent>
#include <QPushButton>
#include <fstream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void init();
    void showmap();
    //void keyPressEvent(QKeyEvent *e);
    int get(const int &, const int &);
    bool checkFinish();
    bool specialPass();
    ~MainWindow();

public slots:
    void setMainMenu();
    void setMission1();
    void setMission2();
    void exitGame();
    void setMission();
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void addMoves();
    void gotoMission();
    void cleanData();

private:
    Ui::MainWindow *ui;
    int mission = 0;
    int map[7][7] = {}; // 0:ground, 1:wall, 2:box
    bool location[7][7] = {};
    int steps = 0;
    bool finish1 = false;
    bool finish2 = false;
    QLabel *label[7][7];
    QLabel *role;
    QLabel *moves;
    QLabel *moveText;
    QLabel *clear1;
    QLabel *clear2;
    QPushButton *restart;
    QPushButton *quit;
    QPushButton *menu;
    QPushButton *startGame;
    QPushButton *mission1;
    QPushButton *mission2;
    QPushButton *quitGame;
    QPushButton *upbtn;
    QPushButton *downbtn;
    QPushButton *leftbtn;
    QPushButton *rightbtn;
    QPushButton *clearData;
    std::fstream file;
};

#endif // MAINWINDOW_H
