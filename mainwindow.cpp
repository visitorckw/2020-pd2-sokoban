#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    for(int i = 0; i < 7; i++)
        for(int j = 0; j < 7; j++)
            label[i][j] = new QLabel(this);
    role = new QLabel(this);
    moves = new QLabel(this);
    moveText = new QLabel(this);
    clear1 = new QLabel(this);
    clear2 = new QLabel(this);
    restart = new QPushButton(this);
    quit = new QPushButton(this);
    menu = new QPushButton(this);
    startGame = new QPushButton(this);
    mission1 = new QPushButton(this);
    mission2 = new QPushButton(this);
    quitGame = new QPushButton(this);
    upbtn = new QPushButton(this);
    downbtn = new QPushButton(this);
    leftbtn = new QPushButton(this);
    rightbtn = new QPushButton(this);
    clearData = new QPushButton(this);
    connect(restart,SIGNAL(clicked()),this,SLOT(setMission()));
    connect(quit,SIGNAL(clicked()),this,SLOT(exitGame()));
    connect(menu,SIGNAL(clicked()),this,SLOT(setMainMenu()));
    connect(startGame,SIGNAL(clicked()),this,SLOT(gotoMission()));
    connect(mission1,SIGNAL(clicked()),this,SLOT(setMission1()));
    connect(mission2,SIGNAL(clicked()),this,SLOT(setMission2()));
    connect(quitGame,SIGNAL(clicked()),this,SLOT(exitGame()));
    connect(upbtn,SIGNAL(clicked()),this,SLOT(moveUp()));
    connect(downbtn,SIGNAL(clicked()),this,SLOT(moveDown()));
    connect(leftbtn,SIGNAL(clicked()),this,SLOT(moveLeft()));
    connect(rightbtn,SIGNAL(clicked()),this,SLOT(moveRight()));
    connect(clearData,SIGNAL(clicked()),this,SLOT(cleanData()));
    init();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init(){
    QPixmap playerPic(":/picture/pusheen.png");
    for(int i = 0; i < 7; i++)
        for(int j = 0; j < 7; j++)
            label[i][j]->setGeometry(100 * i, 100 * j,100,100);
    role->setGeometry(200,400,100,100);
    role->setPixmap(playerPic.scaled(role->width(),role->height(),Qt::KeepAspectRatio));
    moves->setGeometry(900,100,100,100);
    moves->setNum(steps);
    moveText->setGeometry(800,100,100,100);
    moveText->setText("MOVES:");
    clear1->setGeometry(1200,300,200,100);
    clear1->setText("Mission1 Clear!");
    clear2->setGeometry(1200,400,200,100);
    clear2->setText("Mission2 Clear!");
    restart->setGeometry(900,200,100,100);
    quit->setGeometry(1000,200,100,100);
    menu->setGeometry(1100,200,100,100);
    startGame->setGeometry(200,100,100,50);
    mission1->setGeometry(200,200,100,50);
    mission2->setGeometry(200,300,100,50);
    quitGame->setGeometry(200,400,100,50);
    clearData->setGeometry(200,500,100,50);
    restart->setText("restart");
    quit->setText("quit");
    menu->setText("menu");
    startGame->setText("startGame");
    mission1->setText("mission1");
    mission2->setText("mission2");
    quitGame->setText("quitGame");
    clearData->setText("clearData");
    upbtn->setGeometry(900,400,100,100);
    downbtn->setGeometry(900,500,100,100);
    leftbtn->setGeometry(800,500,100,100);
    rightbtn->setGeometry(1000,500,100,100);
    upbtn->setText("UP");
    downbtn->setText("DOWN");
    leftbtn->setText("LEFT");
    rightbtn->setText("RIGHT");

    clear1->setVisible(finish1);
    clear2->setVisible(finish2);

    file.open("gameData.txt",std::ios::in);
    int flag;
    file >> flag;
    if(flag == 1){
        setMission1();
        for(int i = 0; i < 7; i++)
            for(int j = 0; j < 7; j++)
                file >> map[i][j] >> location[i][j];
        int x, y;
        file >> x >> y;
        file >> steps;
        file >> finish1 >> finish2;
        showmap();
        role->move(x,y);
        moves->setNum(steps);
        clear1->setVisible(finish1);
        clear2->setVisible(finish2);
    }
    else if(flag == 2){
        setMission2();
        for(int i = 0; i < 7; i++)
            for(int j = 0; j < 7; j++)
                file >> map[i][j] >> location[i][j];
        int x, y;
        file >> x >> y;
        file >> steps;
        file >> finish1 >> finish2;
        showmap();
        role->move(x,y);
        moves->setNum(steps);
        clear1->setVisible(finish1);
        clear2->setVisible(finish2);
    }
    else setMainMenu();
    file.close();
}

void MainWindow::showmap(){
    QPixmap boxPic(":/picture/aed2bd5d22cf4c7044ff0072c6737d86_script-library_512-512.png");
    QPixmap playerPic(":/picture/pusheen.png");
    QPixmap groundPic(":/picture/grass.jpg");
    QPixmap wallPic(":/picture/brick.jpg");
    QPixmap locationPic(":/picture/destination.jpg");

    for(int i = 0; i < 7; i++){
        for(int j = 0; j < 7; j++){
            switch(map[i][j]){
                case 0:
                    if(location[i][j])
                        label[i][j]->setPixmap(locationPic.scaled(label[i][j]->width(),label[i][j]->height(),Qt::KeepAspectRatio));
                    else
                        label[i][j]->setPixmap(groundPic.scaled(label[i][j]->width(),label[i][j]->height(),Qt::KeepAspectRatio));
                    break;
                case 1:
                    label[i][j]->setPixmap(wallPic.scaled(label[i][j]->width(),label[i][j]->height(),Qt::KeepAspectRatio));
                    break;
                case 2:
                    label[i][j]->setPixmap(boxPic.scaled(label[i][j]->width(),label[i][j]->height(),Qt::KeepAspectRatio));
                    break;
            }
        }
    }
}

int MainWindow::get(const int &x, const int &y){
    if(x < 0 or y < 0 or x >= 7 or y >= 7)
        return 1;
    return map[x][y];
}


void MainWindow::setMainMenu(){
    mission = 0;
    steps = 0;
    moves->setNum(steps);
    for(int i = 0; i < 7; i++)
        for(int j = 0; j < 7; j++)
            label[i][j]->setVisible(false);
    role->setVisible(false);
    startGame->setVisible(true);
    mission1->setVisible(true);
    mission2->setVisible(finish1);
    quitGame->setVisible(true);
    clearData->setVisible(true);
}
void MainWindow::setMission1(){
    mission = 1;
    steps = 0;
    moves->setNum(steps);
    for(int i = 0; i < 7; i++)
        for(int j = 0; j < 7; j++)
            label[i][j]->setVisible(true);
    role->setVisible(true);
    startGame->setVisible(false);
    mission1->setVisible(false);
    mission2->setVisible(false);
    quitGame->setVisible(false);
    clearData->setVisible(false);
    role->move(200,300);
        for(int i = 0; i < 7; i++){
            for(int j = 0; j < 7; j++){
                map[i][j] = 0;
                location[i][j] = false;
            }
        }
        map[1][2] = map[2][2] = map[3][2] = 2;
        map[0][1] = map[1][3] = map[3][0] =
        map[3][1] = map[3][4] = 1;
        location[4][4] = location[0][4] = location[4][0] = true;
    showmap();
}
void MainWindow::setMission2(){
    mission = 2;
    steps = 0;
    moves->setNum(steps);
    for(int i = 0; i < 7; i++)
        for(int j = 0; j < 7; j++)
            label[i][j]->setVisible(true);
    role->setVisible(true);
    startGame->setVisible(false);
    mission1->setVisible(false);
    mission2->setVisible(false);
    quitGame->setVisible(false);
    clearData->setVisible(false);
    role->move(200,200);
    for(int i = 0; i < 7; i++){
        for(int j = 0; j < 7; j++){
            map[i][j] = 0;
            location[i][j] = false;
        }
    }
    map[2][3] = map[3][3] = map[4][3] = 2;
    map[1][1] = map[1][2] = map[2][1] = 1;
    map[5][1] = map[4][1] = map[5][2] = 1;
    map[1][5] = map[1][4] = map[2][5] = 1;
    location[0][0] = location[0][6] = location[6][0] = true;
    showmap();
}

void MainWindow::exitGame(){
    file.open("gameData.txt",std::ios::out);
    file << mission << '\n';
    for(int i = 0; i < 7; i++)
        for(int j = 0; j < 7; j++)
            file << map[i][j] << ' ' << location[i][j] << ' ';
    file << role->x() << ' ' << role->y() << '\n';
    file << steps << '\n';
    file << finish1 << ' ' << finish2 << '\n';
    QApplication *app;
    app->exit(0);
}

void MainWindow::moveUp(){
    const int x = role->x() / 100;
    const int y = role->y() / 100;
    bool canMove = true;
    int i;
    if(get(x,y-1) != 2) {
        if(get(x,y-1) != 1){
            role->move(role->x(), role->y() - 100);
            addMoves();
        }
        return;
    }
    for(i = y - 1;; i--){
        if(get(x,i) == 1){
            canMove = false;
            break;
        }
        else if(!get(x,i))
            break;
    }
    if(canMove){
        map[x][y-1] = 0;
        map[x][i] = 2;
        showmap();
        role->move(role->x(), role->y() - 100);
        addMoves();
    }
    if(checkFinish()){
        if(mission == 1) {
            finish1 = true;
            clear1->setVisible(true);
        }
        else if(mission == 2) {
            finish2 = true;
            clear2->setVisible(true);
        }
        setMainMenu();
    }
}
void MainWindow::moveDown(){
    const int x = role->x() / 100;
    const int y = role->y() / 100;
    bool canMove = true;
    int i;
    if(get(x,y+1) != 2) {
        if(get(x,y+1) != 1){
            role->move(role->x(), role->y() + 100);
            addMoves();
        }
        return;
    }
    for(i = y + 1;; i++){
        if(get(x,i) == 1){
            canMove = false;
            break;
        }
        else if(!get(x,i))
            break;
    }
    if(canMove){
        map[x][y+1] = 0;
        map[x][i] = 2;
        showmap();
        role->move(role->x(), role->y() + 100);
        addMoves();
    }
    if(checkFinish()){
        if(mission == 1) {
            finish1 = true;
            clear1->setVisible(true);
        }
        else if(mission == 2) {
            finish2 = true;
            clear2->setVisible(true);
        }
        setMainMenu();
    }
}
void MainWindow::moveLeft(){
    const int x = role->x() / 100;
    const int y = role->y() / 100;
    bool canMove = true;
    int i;
    if(get(x-1,y) != 2) {
        if(get(x-1,y) != 1){
            role->move(role->x() - 100, role->y());
            addMoves();
        }
        return;
    }
    for(i = x - 1;; i--){
        if(get(i,y) == 1){
            canMove = false;
            break;
        }
        else if(!get(i,y))
            break;
    }
    if(canMove){
        map[x-1][y] = 0;
        map[i][y] = 2;
        showmap();
        role->move(role->x() - 100, role->y());
        addMoves();
    }
    if(checkFinish()){
        if(mission == 1) {
            finish1 = true;
            clear1->setVisible(true);
        }
        else if(mission == 2) {
            finish2 = true;
            clear2->setVisible(true);
        }
        setMainMenu();
    }
}
void MainWindow::moveRight(){
    const int x = role->x() / 100;
    const int y = role->y() / 100;
    bool canMove = true;
    int i;
    if(get(x+1,y) != 2) {
        if(get(x+1,y) != 1){
            role->move(role->x() + 100, role->y());
            addMoves();
        }
        return;
    }
    for(i = x + 1;; i++){
        if(get(i,y) == 1){
            canMove = false;
            break;
        }
        else if(!get(i,y))
            break;
    }
    if(canMove){
        map[x+1][y] = 0;
        map[i][y] = 2;
        showmap();
        role->move(role->x() + 100, role->y());
        addMoves();
    }
    if(checkFinish()){
        if(mission == 1) {
            finish1 = true;
            clear1->setVisible(true);
        }
        else if(mission == 2) {
            finish2 = true;
            clear2->setVisible(true);
        }
        setMainMenu();
    }
}
void MainWindow::addMoves(){
    moves->setNum(++steps);
    if(specialPass()){
        if(mission == 1) {
            finish1 = true;
            clear1->setVisible(true);
        }
        else if(mission == 2) {
            finish2 = true;
            clear2->setVisible(true);
        }
        setMainMenu();
    }
}
bool MainWindow::checkFinish(){
    for(int i = 0; i < 7; i++)
        for(int j = 0; j < 7; j++)
            if(location[i][j] && map[i][j] != 2)
                return false;
    return true;
}

void MainWindow::setMission(){
    if(mission == 1){
        setMission1();
        return;
    }
    if(mission == 2)
        setMission2();
}
void MainWindow::gotoMission(){
    if(finish1){
        setMission2();
        return;
    }
    else {
        setMission1();
    }
}
bool MainWindow::specialPass(){
    if(role->x() == 600 and role->y() == 600)
        return true;
    return false;
}

void MainWindow::cleanData(){
    file.open("gameData.txt",std::ios::out);
    file << 0;
    QApplication *app;
    app->exit(0);
}
/*void MainWindow::keyPressEvent(QKeyEvent *e){
    const int x = role->x() / 100;
    const int y = role->y() / 100;
    bool canMove = true;
    int i;
    switch(e->key()){
        case Qt::Key_Up:
            if(map[x][y-1] != 2) {
                if(map[x][y-1] != 1)
                    role->move(role->x(), role->y() - 100);
                break;
            }
            for(i = y - 1;; i--){
                if(get(x,i) == 1){
                    canMove = false;
                    break;
                }
                else if(!get(x,i))
                    break;
            }
            if(canMove){
                map[x][y-1] = 0;
                map[x][i] = 2;
                showmap();
                role->move(role->x(), role->y() - 100);
            }
            break;
        case Qt::Key_Down:
            if(map[x][y+1] != 2) {
                if(map[x][y+1] != 1)
                    role->move(role->x(), role->y() + 100);
                break;
            }
            for(i = y + 1;; i++){
                if(get(x,i) == 1){
                    canMove = false;
                    break;
                }
                else if(!get(x,i))
                    break;
            }
            if(canMove){
                map[x][y+1] = 0;
                map[x][i] = 2;
                showmap();
                role->move(role->x(), role->y() + 100);
            }
            break;
        case Qt::Key_Left:
            if(map[x-1][y] != 2) {
                if(map[x-1][y] != 1)
                    role->move(role->x() - 100, role->y());
                break;
            }
            for(i = x - 1;; i--){
                if(get(i,y) == 1){
                    canMove = false;
                    break;
                }
                else if(!get(i,y))
                    break;
            }
            if(canMove){
                map[x-1][y] = 0;
                map[i][y] = 2;
                showmap();
                role->move(role->x() - 100, role->y());
            }
            break;
        case Qt::Key_Right:
            if(map[x+1][y] != 2) {
                if(map[x+1][y] != 1)
                    role->move(role->x() + 100, role->y());
                break;
            }
            for(i = x + 1;; i++){
                if(get(i,y) == 1){
                    canMove = false;
                    break;
                }
                else if(!get(i,y))
                    break;
            }
            if(canMove){
                map[x+1][y] = 0;
                map[i][y] = 2;
                showmap();
                role->move(role->x() + 100, role->y());
            }
            break;
    }
}*/
