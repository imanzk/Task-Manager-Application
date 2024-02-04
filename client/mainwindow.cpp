#include "mainwindow.h"


void MainWindow::repeat()
{
    // QThread::msleep(2000);
    if(place == admin::home){
        if(hom&&!hom->sort&&hom->filter=="all")
            createHome();
    }
    else if(place == admin::organization){
        if(organ&&!organ->sortteam&&!organ->sortproject&&organ->filterteam=="all"&&organ->filterproject=="all")
            createOrgan();
    }
    else if(place == admin::about_organization){
        if(curOrgan.role != "manager")
            createAboutorganization();
    }
    else if(place == admin::team){
        createTeam();
    }else if(place == admin::task){
        if(curOrgan.role == "member")
            createTask();
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    //socket
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::readSocket);
    connect(socket, &QTcpSocket::disconnected, this, &MainWindow::discardSocket);
    connect(socket, &QAbstractSocket::errorOccurred, this, &MainWindow::displayError);
    connect(this , &MainWindow::newMessage , this , &MainWindow::get);
    socket->connectToHost(QHostAddress::LocalHost ,8080);
    if(!socket->waitForConnected(500)){
        qDebug("Error to Connect!");
        exit(EXIT_FAILURE);
    }
    qDebug()<<"connected";
    //
    for(int i = 0; i < SIZE ; i++)
        component[i] = nullptr;

    stack = new QStackedWidget;
    stack->setFixedSize(1000,600);
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    QPoint center = screenGeometry.center();
    stack->move(center - stack->rect().center());
    // run start
    QDir dir;
    QString path = dir.path() + "/user.txt";
    QFileInfo fileInfo(path);
    if (fileInfo.exists()) {
        QFile file(path);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            in >> curUser.username;
            if(curUser.username.isEmpty()){
                create(com_type::entrance);
            }
            else{
                send("client "+curUser.username);
                createHome();
            }
            file.close();
        }
    }else create(com_type::entrance);
    //
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this , &MainWindow::repeat);
    timer->start(10000);
}

MainWindow::~MainWindow()
{
    if(socket->isOpen())
        socket->close();
    for(int i = 0 ; i < SIZE ; i++)
        if(component[i])delete component[i];
}

void MainWindow::readSocket()
{
    QByteArray buffer;

    QDataStream socketStream(socket);

    socketStream.setVersion(QDataStream::Qt_5_15);

    socketStream.startTransaction();
    socketStream >> buffer;

    if(!socketStream.commitTransaction())
    {
        QString message = QString("%1 :: Waiting for more data to come..").arg(socket->socketDescriptor());
        emit newMessage(message);
        return;
    }

    QString header = buffer.mid(0,128);
    QString fileType = header.split(",")[0].split(":")[1];

    buffer = buffer.mid(128);

    if(fileType=="message"){
        // QString message = QString("%1 :: %2").arg(socket->socketDescriptor()).arg(QString::fromStdString(buffer.toStdString()));
        QString message = QString::fromStdString(buffer.toStdString());
        emit newMessage(message);
    }
}

void MainWindow::discardSocket()
{
    socket->deleteLater();
    socket=nullptr;

    qDebug("Disconnected!");
}

void MainWindow::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        qDebug("The host was not found. Please check the host name and port settings.");
        break;
    case QAbstractSocket::ConnectionRefusedError:
        qDebug("The connection was refused by the peer. Make sure QTCPServer is running, and check that the host name and port settings are correct.");
        break;
    default:
        qDebug("Unknown Error!");
        break;
    }
}

void MainWindow::send(QString str)
{
    qDebug()<<"submit:"<<str;
    socket->write(str.toUtf8().constData());
    socket->waitForBytesWritten(100);
}

void MainWindow::create(com_type type){
    place = PLACE::null;
    QWidget **comp = &component[type];
    if(*comp)
    {
        stack->removeWidget(*comp);
        disconnect(*comp);
        delete *comp;
        *comp = nullptr;
    }
    switch(type){
    case com_type::entrance:
        *comp=new EntrancePage;
        stack->setWindowTitle("Entrance");
        connect(*comp,SIGNAL(_click(Entrance::key_type))
                ,this,SLOT(entranceFunc(Entrance::key_type)));
        break;
    case com_type::login:
        *comp=new LogInPage;
        stack->setWindowTitle("Login");
        connect(*comp,SIGNAL(_click(LogIn::key_type,User))
                ,this,SLOT(loginFunc(LogIn::key_type,User)));
        break;
    case com_type::signup:
        *comp=new SignUpPage;
        stack->setWindowTitle("Signup");
        connect(*comp,SIGNAL(_click(SignUp::key_type,User))
                ,this,SLOT(signupFunc(SignUp::key_type,User)));
        break;
    }

    stack->setFixedSize(1000,600);
    stack->addWidget(*comp);
    stack->setCurrentWidget(*comp);
    stack->show();
}

void MainWindow::createRec()
{
    place = PLACE::create_recovery;
    stack->setEnabled(false);
    QDialog *dialog = new QDialog();
    rec = new recovery(dialog);
    dialog->move(pos() + (QGuiApplication::primaryScreen()->geometry().center() - geometry().center()));
    dialog->show();
    connect(dialog,&QDialog::finished , [&](){stack->setEnabled(true);});
    connect(rec,&recovery::_click , this , &MainWindow::recFunc);
}

void MainWindow::createHome()
{
    place = PLACE::home;
    hom = new home;
    stack->setWindowTitle("Home");
    connect(hom , &home::_click , this , &MainWindow::homFunc);
    stack->addWidget(hom);
    stack->setCurrentWidget(hom);
    stack->show();
    //
    send("home SELECT * FROM 'organization_member' WHERE username = '"+curUser.username+"'");
}

void MainWindow::createCreateorgan()
{
    place = PLACE::create_organization;
    stack->setEnabled(false);
    QDialog *dialog = new QDialog();
    createorgan = new createorganization(dialog);
    dialog->move(pos() + (QGuiApplication::primaryScreen()->geometry().center() - geometry().center()));
    dialog->show();
    connect(dialog,&QDialog::finished , [&](){stack->setEnabled(true);});
    connect(createorgan,&createorganization::_click , this , &MainWindow::createorganFunc);
}

void MainWindow::createOrgan()
{
    place = PLACE::organization;
    organ = new organization;
    organ->curOrgan = curOrgan;
    stack->setWindowTitle(curOrgan.name + " organization");
    connect(organ , &organization::_click , this , &MainWindow::organFunc);
    stack->addWidget(organ);
    stack->setCurrentWidget(organ);
    stack->show();
    //
    send("getrole SELECT * FROM 'organization_member' WHERE name = '"+curOrgan.name+"' AND username ='"+curUser.username+"'");
    // QThread::msleep(1);
}

void MainWindow::createCreateTeam()
{
    place = PLACE::create_team;
    stack->setEnabled(false);
    QDialog *dialog = new QDialog();
    createmyteam = new createteam(dialog);
    dialog->move(pos() + (QGuiApplication::primaryScreen()->geometry().center() - geometry().center()));
    dialog->show();
    connect(dialog,&QDialog::finished , [&](){stack->setEnabled(true);});
    connect(createmyteam,&createteam::_click , this , &MainWindow::createteamFunc);
}

void MainWindow::createCreateProject()
{
    place = PLACE::create_project;
    stack->setEnabled(false);
    QDialog *dialog = new QDialog();
    createmyproject = new createproject(dialog);
    dialog->move(pos() + (QGuiApplication::primaryScreen()->geometry().center() - geometry().center()));
    dialog->show();
    connect(dialog,&QDialog::finished , [&](){stack->setEnabled(true);});
    connect(createmyproject,&createproject::_click , this , &MainWindow::createprojectFunc);
}

void MainWindow::createAboutorganization()
{
    place = PLACE::about_organization;
    aboutorgan = new aboutorganization;
    aboutorgan->displayOrgan(curOrgan);
    stack->setWindowTitle("about "+ curOrgan.name);
    connect(aboutorgan , &aboutorganization::_click , this , &MainWindow::aboutorganFunc);
    stack->addWidget(aboutorgan);
    stack->setCurrentWidget(aboutorgan);
    stack->show();
    //
    send("getmemberorg SELECT * FROM 'organization_member' WHERE name = '"+curOrgan.name+"'");
}

void MainWindow::createAddmember()
{
    // place = PLACE::add_member;
    stack->setEnabled(false);
    QDialog *dialog = new QDialog();
    addmemb = new addmemberClass(dialog);
    dialog->move(pos() + (QGuiApplication::primaryScreen()->geometry().center() - geometry().center()));
    dialog->show();
    connect(dialog,&QDialog::finished , [&](){stack->setEnabled(true);});
    connect(addmemb,&addmemberClass::_click , this , &MainWindow::addmemberFunc);
}

void MainWindow::createMembersetting()
{
    place = PLACE::member_setting;
    stack->setEnabled(false);
    QDialog *dialog = new QDialog();
    memberset = new membersetting(dialog);
    memberset->init(curMember);
    dialog->move(pos() + (QGuiApplication::primaryScreen()->geometry().center() - geometry().center()));
    dialog->show();
    connect(dialog,&QDialog::finished , [&](){stack->setEnabled(true);});
    connect(memberset,&membersetting::_click , this , &MainWindow::membersettingFunc);
}

void MainWindow::createTeam() //mycreateteam
{
    place = PLACE::team;
    prevKind = "team";
    myteam = new team;
    myteam->curTeam = curTeam;
    myteam->curOrg = curOrgan;
    stack->setWindowTitle(curTeam.name + " team in "+curOrgan.name+" organization");
    connect(myteam , &team::_click , this , &MainWindow::teamFunc);
    stack->addWidget(myteam);
    stack->setCurrentWidget(myteam);
    stack->show();
    //
    if(curOrgan.role != "member"){
        myteam->curTeam.role=curOrgan.role;
        send("getmemberteam SELECT * FROM 'team_member' WHERE name = '"+curTeam.name+"'");
    }
    else{
        send("curteam SELECT * FROM 'team_member' WHERE name='"+curTeam.name+"' AND username='"+curUser.username+"'");
    }
}

void MainWindow::createMembersettingteam()
{
    place = PLACE::member_setting_team;
    stack->setEnabled(false);
    QDialog *dialog = new QDialog();
    mymembersettingteam = new membersettingteam(dialog);
    mymembersettingteam->init(curMember);
    dialog->move(pos() + (QGuiApplication::primaryScreen()->geometry().center() - geometry().center()));
    dialog->show();
    connect(dialog,&QDialog::finished , [&](){stack->setEnabled(true);});
    connect(mymembersettingteam,&membersettingteam::_click , this , &MainWindow::membersettingteamFunc);
}

void MainWindow::createCreateTask()
{
    place = PLACE::create_task;
    stack->setEnabled(false);
    QDialog *dialog = new QDialog();
    createmytask = new createtask(dialog);
    dialog->move(pos() + (QGuiApplication::primaryScreen()->geometry().center() - geometry().center()));
    dialog->show();
    connect(dialog,&QDialog::finished , [&](){stack->setEnabled(true);});
    connect(createmytask,&createtask::_click , this , &MainWindow::createtaskFunc);
}

void MainWindow::createTask()
{
    place = PLACE::task;
    mytask = new task;
    mytask->curOrgan = curOrgan;
    mytask->curTeam = curTeam;
    connect(mytask , &task::_click , this , &MainWindow::taskFunc);
    stack->addWidget(mytask);
    stack->setCurrentWidget(mytask);
    stack->show();
    //
    send("curtask SELECT * FROM task WHERE name='"+curTask.name+"'");
}

void MainWindow::createAddcomment()
{
    place = PLACE::add_comment;
    stack->setEnabled(false);
    QDialog *dialog = new QDialog();
    addcom = new addcomment(dialog);
    dialog->move(pos() + (QGuiApplication::primaryScreen()->geometry().center() - geometry().center()));
    dialog->show();
    connect(dialog,&QDialog::finished , [&](){stack->setEnabled(true);});
    connect(addcom,&addcomment::_click , this , &MainWindow::addcommentFunc);
}

void MainWindow::createAboutTeam()
{
    place = PLACE::about_team;
    stack->setEnabled(false);
    QDialog *dialog = new QDialog();
    aboutmyteam = new aboutteam(dialog);
    dialog->move(pos() + (QGuiApplication::primaryScreen()->geometry().center() - geometry().center()));
    dialog->show();
    connect(dialog,&QDialog::finished , [&](){stack->setEnabled(true);});
    connect(aboutmyteam,&aboutteam::_click , this , &MainWindow::aboutteamFunc);
    //
    send("getaboutteam SELECT * FROM team WHERE name='"+curTeam.name+"'");
}

void MainWindow::createProject()
{
    place = PLACE::project;
    prevKind = "project";
    myproject = new project;
    myproject->curProject = curProject;
    myproject->curOrgan = curOrgan;
    stack->setWindowTitle(curProject.name + " project in "+curOrgan.name+" organization");
    connect(myproject , &project::_click , this , &MainWindow::projectFunc);
    stack->addWidget(myproject);
    stack->setCurrentWidget(myproject);
    stack->show();
    //
    send("getmemberproject SELECT * FROM 'project_member' WHERE name = '"+curProject.name+"'");

}

void MainWindow::createAboutProject()
{
    place = PLACE::about_project;
    stack->setEnabled(false);
    QDialog *dialog = new QDialog();
    aboutmyproject = new aboutproject(dialog);
    dialog->move(pos() + (QGuiApplication::primaryScreen()->geometry().center() - geometry().center()));
    dialog->show();
    connect(dialog,&QDialog::finished , [&](){stack->setEnabled(true);});
    connect(aboutmyproject,&aboutproject::_click , this , &MainWindow::aboutprojectFunc);
    //
    send("getaboutproject SELECT * FROM project WHERE name='"+curProject.name+"'");
}

void MainWindow::entranceFunc(Entrance::key_type type)
{
    type==Entrance::login?create(com_type::login)
                            :create(com_type::signup);
}
void MainWindow::signupFunc(SignUp::key_type type,User data)
{
    try{
        if(type == SignUp::key_type::cancel)
            create(com_type::entrance);
        else{
            auto comp = dynamic_cast<SignUpPage*>(component[com_type::signup]);
            this->send("INSERT INTO user (name, email, username , password) VALUES ('"+data.name+"','"+data.email+"','"+data.username+"','"+data.password+"')");
        }
    }catch(program_exception e){
        qDebug() << e.what();
    }
}
void MainWindow::loginFunc(LogIn::key_type type,User data)
{
    try{
        if(type == LogIn::key_type::cancel)
            create(com_type::entrance);
        else if(type == LogIn::key_type::recovery){
            createRec();
        }
        else{
            send("SELECT * FROM user WHERE username = '"+data.username+"' and password = '"+data.password+"'");
            curUser = data;
        }
    }catch(program_exception e){
        qDebug() << e.what();
    }
}

void MainWindow::recFunc(User data)
{
    send("recovery SELECT password FROM user WHERE username = '"+data.username+"' and email = '"+data.email+"'");
}

void MainWindow::homFunc(HOME t, Organization org)
{
    if(t == HOME::create){
        createCreateorgan();
    }else if(t == HOME::filter){
        //
    }
    else if(t == HOME::logout){
        create(com_type::entrance);
        QDir dir;
        QString path = dir.path() + "/user.txt";
        QFile file(path);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            // QTextStream out(&file);
            // out << curUser.username << "\n";
            file.close();
        }
    }else if(t == HOME::organclick){
        curOrgan = org;
        createOrgan();
    }
    else if(t == HOME::sort){
        //
    }else if(t == HOME::tasks){

    }
}

void MainWindow::createorganFunc(Organization org)
{
    send("org INSERT INTO organization (name, type, description) VALUES ('"+org.name+"','"+org.type+"','"+org.description+"')");
    curOrgan = org;
}

void MainWindow::organFunc(ORGAN type, Group g) //myorganfunc
{
    if(ORGAN::home == type){
        createHome();
    }
    else if(ORGAN::createTeam == type){
        createCreateTeam();
    }else if(ORGAN::creatProject == type){
        createCreateProject();
    }else if(ORGAN::about == type){
        createAboutorganization();
    }else if(ORGAN::teamclick == type){
        curTeam.name = g.name;
        createTeam();
    }else if(ORGAN::projectclick == type){
        curProject.name = g.name;
        createProject();
    }
}

void MainWindow::createteamFunc(Team team)
{
    send("team INSERT INTO team (name, department, description) VALUES ('"+team.name+"','"+team.department+"','"+team.description+"')");
    curTeam = team;
}

void MainWindow::createprojectFunc(Project project)
{
    send("project INSERT INTO project (name, goal, description) VALUES ('"+project.name+"','"+project.goal+"','"+project.description+"')");
    curProject = project;
}

void MainWindow::aboutorganFunc(ABOUTORGAN t,Organization org)
{
    if(t == ABOUTORGAN::addmember){
        createAddmember();
    }
    else if(t == ABOUTORGAN::back){
        createOrgan();
    }
    else if(t == ABOUTORGAN::edit){
        send("editorgan UPDATE organization SET type='"+org.type+"' , description='"+org.description+"' WHERE name='"+org.name+"'");
    }
    else if(t == ABOUTORGAN::memberclick){
        curMember.username = org.username;
        curMember.role = org.role;
        createMembersetting();
    }else if(t == ABOUTORGAN::remove){
        send("removeorgan "+curOrgan.name);
    }
}

void MainWindow::addmemberFunc(ADDMEMBER t, User u)
{
    QString type1;
    QString type2;
    QString name;
    QString table;
    if(place == PLACE::team){
        type1 = "addmemberteam";
        type2 = "searchmemberteam";
        table = "team_member";
        name = curTeam.name;
    }else if(place == PLACE::about_organization){
        type1 = "addmember";
        type2 = "searchmember";
        table = "organization_member";
        name = curOrgan.name;
    }else if(place == PLACE::project){
        type1 = "addmemberproject";
        type2 = "searchmemberproject";
        table = "project_member";
        name = curProject.name;
    }else if(place == PLACE::task){
        type1 = "addmembertask";
        type2 = "searchmembertask";
        table = "task_member";
        name = curTask.name;
    }
    if(ADDMEMBER::userclick == t){
        if(place==PLACE::team||place==PLACE::about_organization)send(type1+" INSERT INTO '"+table+"' (name , username , role) VALUES ('"+name+"','"+u.username+"','member') ");
        else if(place==PLACE::project)send(type1+" INSERT INTO '"+table+"' (name , username) VALUES ('"+name+"','"+u.username+"') ");
        else send(type1+" INSERT INTO '"+table+"' (name , username) VALUES ('"+name+"','"+u.username+"') ");
        auto com = dynamic_cast<QDialog*>(addmemb->parent());
        com->close();

    }else if(ADDMEMBER::search == t){
        send(type2+" "+u.username+" "+name+" "+curOrgan.name);
    }
}

void MainWindow::membersettingFunc(MEMBERSETTING t, User u)
{
    if(t == MEMBERSETTING::clear){
        send("membersetting DELETE FROM 'organization_member' WHERE username='"+u.username+"' AND name='"+curOrgan.name+"'");
    }else if(t == MEMBERSETTING::disgrade){
        send("membersetting UPDATE 'organization_member' SET role='member' WHERE name='"+curOrgan.name+"' AND username='"+u.username+"'");
    }else if(t == MEMBERSETTING::upgrade){
        send("membersetting UPDATE 'organization_member' SET role='admin' WHERE name='"+curOrgan.name+"' AND username='"+u.username+"'");
    }
}

void MainWindow::teamFunc(TEAM::t type, Team team)
{
    if(type == TEAM::about){
        createAboutTeam();
    }else if(type == TEAM::addmember){
        createAddmember();
    }else if(type == TEAM::addtask){
        createCreateTask();
    }else if(type == TEAM::back){
        createOrgan();
    }else if(type == TEAM::memberclick){
        curMember.username = team.username;
        curMember.role = team.role;
        createMembersettingteam();
    }else if(type == TEAM::taskclick){
        curTask = team.task;
        createTask();
    }
}

void MainWindow::membersettingteamFunc(MEMBERSETTINGTEAM::t t, User u)
{
    if(t == MEMBERSETTINGTEAM::clear){
        send("membersettingteam DELETE FROM 'team_member' WHERE username='"+u.username+"' AND name='"+curTeam.name+"'");
    }else if(t == MEMBERSETTINGTEAM::disgrade){
        send("membersettingteam UPDATE 'team_member' SET role='member' WHERE name='"+curTeam.name+"' AND username='"+u.username+"'");
    }else if(t == MEMBERSETTINGTEAM::upgrade){
        send("membersettingteam UPDATE 'team_member' SET role='director' WHERE name='"+curTeam.name+"' AND username='"+u.username+"'");
    }
}

void MainWindow::createtaskFunc(Task task)
{
    send("createtask INSERT INTO task (name, date, description) VALUES ('"+task.name+"','"+task.date+"','"+task.description+"')");
    curTask = task;
}

void MainWindow::taskFunc(TASKPAGE::t type, Task task)
{
    if(type == TASKPAGE::addcomment){
        createAddcomment();
    }else if(type == TASKPAGE::addmember){
        createAddmember();
    }else if(type == TASKPAGE::commentclick){
        send("removecomment DELETE FROM task_comment WHERE task='"+task.name+"' AND comment='"+task.comment+"'");
        createTask();
    }else if(type == TASKPAGE::memberclick){
        send("removemembertask DELETE FROM task_member WHERE name='"+task.name+"' AND username='"+task.user.username+"'");
        createTask();
    }else if(type == TASKPAGE::edit){
        send("edittask UPDATE task SET description='"+task.description+"' , date='"+task.date+"' WHERE name='"+task.name+"'");
        createTask();
    }else if(type == TASKPAGE::remove){
        send("removetask "+task.name);
        if(prevKind == "team")
            createTeam();
        else if(prevKind == "project")
            createProject();
    }else if(type == TASKPAGE::back){
        if(prevKind == "team")
            createTeam();
        else if(prevKind == "project")
            createProject();
    }
}

void MainWindow::addcommentFunc(QString comment)
{
    comment = curUser.username + ":\n" + comment;
    send("addcomment INSERT INTO task_comment (task , comment) VALUES ('"+curTask.name+"','"+comment+"')");
    auto com = dynamic_cast<QDialog*>(addcom->parent());
    com->close();
    createTask();
}

void MainWindow::aboutteamFunc(ABOUTTEAM::t type, Team team)
{
    if(type == ABOUTTEAM::remove){
        send("removeteam DELETE FROM team WHERE name='"+team.name+"'");
    }else if(type == ABOUTTEAM::edit){
        send("editteam UPDATE team SET description='"+team.description+"' , department='"+team.department+"' WHERE name='"+team.name+"'");
    }
}

void MainWindow::projectFunc(PROJECT::t type, Project project)
{
    if(type == PROJECT::about){
        createAboutProject();
    }else if(type == PROJECT::addmember){
        createAddmember();
    }else if(type == PROJECT::addtask){
        createCreateTask();
    }else if(type == PROJECT::back){
        createOrgan();
    }else if(type == PROJECT::memberclick){
        QString username = project.user.username;
        send("removememberproject DELETE FROM project_member WHERE username='"+username+"'");
    }else if(type == PROJECT::taskclick){
        curTask = project.task;
        createTask();
    }
}

void MainWindow::aboutprojectFunc(ABOUTPROJECT::t type, Project project)
{
    if(type == ABOUTPROJECT::remove){
        send("removeproject DELETE FROM project WHERE name='"+project.name+"'");
    }else if(type == ABOUTPROJECT::edit){
        send("editproject UPDATE project SET description='"+project.description+"' , goal='"+project.goal+"' WHERE name='"+project.name+"'");
    }
}

void MainWindow::get(QString str){
    qDebug() <<"received:"<< str;
    int in = str.indexOf(" ")+1;
    //signup
    if(str == "username exists"){
        auto comp = dynamic_cast<SignUpPage*>(component[com_type::signup]);
        comp->displayMessage(str);
    }else if(str == "user was added"){
        create(com_type::entrance);
    }
    //login
    else if(str == "wrong information"){
        auto comp = dynamic_cast<LogInPage*>(component[com_type::login]);
        comp->displayMessage(str);
    }else if(str == "user was recognized"){
        QDir dir;
        QString path = dir.path() + "/user.txt";
        QFile file(path);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            // Write the text to the file
            QTextStream out(&file);
            out << curUser.username << "\n";
            file.close();
        }
        send("client "+curUser.username);
        // QThread::msleep(1);
        createHome();
    }
    //recovery
    else if(str == "rec wrong email or username"){
        str.remove("rec ");
        rec->display(str);
    }else if(str.split(" ").at(0) == "passwordRec"){
        str.remove("passwordRec ");
        rec->display("your password: "+str);
    }
    //createorgan
    else if(str == "organization name exists"){
        createorgan->display(str);
    }else if(str == "organization was added"){
        send("org "+curUser.username+" "+curOrgan.name);
        auto com = dynamic_cast<QDialog*>(createorgan->parent());
        com->close();
        createHome();
    }
    //home
    else if(str.split(" ").at(0) == "home"){
        if(place != PLACE::home)return;
        str.remove(0 , 5);
        if(str.size()==0) return;
        QStringList l = str.split(" ");
        for(int i = 0 ; i < l.size() ; i += 2){
            Organization org(l[i] , l[i+1]);
            hom->display(org);
        }
    }
    //createteam
    else if(str == "team name exists"){
        createmyteam->display(str);
    }else if(str == "team was added"){
        send("team "+curTeam.name+" "+curOrgan.name);
        auto com = dynamic_cast<QDialog*>(createmyteam->parent());
        com->close();
        createOrgan();
    }
    //createproject
    else if(str == "project name exists"){
        createmyproject->display(str);
    }else if(str == "project was added"){
        send("project "+curProject.name+" "+curOrgan.name);
        auto com = dynamic_cast<QDialog*>(createmyproject->parent());
        com->close();
        createOrgan();
    }
    //createtask
    else if(str == "task name exists"){
        createmytask->display(str);
    }else if(str == "task was added"){
        if(prevKind == "team")
            send("createtask next INSERT INTO 'team_task' (task , team) VALUES ('"+curTask.name+"' , '"+curTeam.name+"')");
        else if(prevKind == "project")
            send("createtask next INSERT INTO 'project_task' (task , project) VALUES ('"+curTask.name+"' , '"+curProject.name+"')");
        auto com = dynamic_cast<QDialog*>(createmytask->parent());
        com->close();
        if(prevKind == "team")
            createTeam();
        else if(prevKind == "project")
            createProject();
    }
    //getteam
    else if(str.split(" ").at(0) == "getteam"){
        if(place != PLACE::organization)return;
        str.remove(0 , 8);
        send("getproject "+curUser.username+" SELECT * FROM 'organization_project' WHERE organization = '"+curOrgan.name+"'");
        //
        if(str.size()==0) return;
        QStringList l = str.split(" ");
        for(int i = 0 ; i < l.size() ; i += 2){
            Team team;
            team.name = l[i];
            team.available = l[i+1]=='1'?true:false;
            organ->display(team);
        }
    }
    //getproject
    else if(str.split(" ").at(0) == "getproject"){
        if(place != PLACE::organization)return;
        str.remove(0 , 11);
        //
        if(str.size()==0) return;
        QStringList l = str.split(" ");
        for(int i = 0 ; i < l.size() ; i += 2){
            Project project;
            project.name = l[i];
            project.available = l[i+1]=='1'?true:false;
            organ->display(project);
        }
    }
    //getmemberorg
    else if(str.split(" ").at(0) == "getmemberorg"){
        if(place != PLACE::about_organization)return;
        str.remove(0 , 13);
        send("curorgan SELECT * FROM organization WHERE name='"+curOrgan.name+"'");
        //
        if(str.size()==0) return;
        QStringList l = str.split(" ");
        for(int i = 0 ; i < l.size() ; i += 2){
            User u;
            u.username = l[i];
            u.role = l[i+1];
            aboutorgan->displayMember(u);
        }
    }
    //editorgan
    else if(str.split(" ").at(0) == "editorgan")
    {
        if(place != PLACE::about_organization)return;
        createAboutorganization();
    }
    //getrole
    else if(str.split(" ").at(0) == "getrole"){
        str.remove(0,8);
        send("getteam "+curUser.username+" SELECT * FROM 'organization_team' WHERE organization = '"+curOrgan.name+"'");
        curOrgan.role = str;
        organ->curOrgan.role = str;
        organ->init();
    }
    //curorgan
    else if(str.split(" ").at(0)== "curorgan"){
        str.remove(0,9);
        QStringList l = str.split(",");
        if(l.size()==0) return;
        if(l.size()>=1)curOrgan.name = l[0];
        if(l.size()>=2)curOrgan.type = l[1];
        if(l.size()>=3)curOrgan.description = l[2];
        aboutorgan->displayOrgan(curOrgan);
    }
    //removeorgan
    else if(str.split(" ").at(0) == "removeorgan"){
        str.remove(0,12);
        if(curOrgan.name == str)createHome();
    }
    //searchmember
    else if(str.split(" ").at(0)== "searchmember"){
        str.remove(0,13);
        QStringList l = str.split(" ");
        if(l.size()==0) return;
        for(auto x:l){
            addmemb->display(x);
        }
    }
    //membersetting
    else if(str == "membersetting"){
        auto com = dynamic_cast<QDialog*>(memberset->parent());
        com->close();
        createAboutorganization();
    }
    //membersettingteam
    else if(str == "membersettingteam"){
        auto com = dynamic_cast<QDialog*>(mymembersettingteam->parent());
        com->close();
        createTeam();
    }
    //getmemberteam
    else if(str.split(" ").at(0) == "getmemberteam"){
        str.remove(0,14);
        send("gettaskteam SELECT * FROM team_task WHERE team='"+curTeam.name+"'");
        if(str.size()==0) return;
        QStringList l = str.split(" ");
        for(int i =0 ;i < l.size() ; i+=2){
            myteam->displayMember(User(l[i],l[i+1]));
        }
    }
    //getmemberproject
    else if(str.split(" ").at(0) == "getmemberproject"){
        str.remove(0,17);
        send("gettaskproject SELECT * FROM project_task WHERE project='"+curProject.name+"'");
        if(str.size()==0) return;
        QStringList l = str.split(" ");
        for(int i =0 ;i < l.size() ; i+=1){
            myproject->displayMember(User(l[i]));
        }
    }
    //gettaskteam
    else if(str.split(" ").at(0) == "gettaskteam"){
        str.remove(0,12);
        if(str.size()==0) return;
        QStringList l = str.split(" ");
        for(int i =0 ;i < l.size() ; i+=1){
            myteam->displayTask(Task(l[i]));
        }
    }
    //gettaskproject
    else if(str.split(" ").at(0) == "gettaskproject"){
        str.remove(0,15);
        if(str.size()==0) return;
        QStringList l = str.split(" ");
        for(int i =0 ;i < l.size() ; i+=1){
            myproject->displayTask(Task(l[i]));
        }
    }
    //curteam
    else if(str.split(" ").at(0) == "curteam"){
        str.remove(0,8);
        QStringList l = str.split(" ");
        curTeam.username = l[0];
        curTeam.name = l[1];
        curTeam.role = l[2];
        myteam->curTeam = curTeam;
        myteam->init();
        send("getmemberteam SELECT * FROM 'team_member' WHERE name = '"+curTeam.name+"'");
    }
    //curtask
    else if(str.split(" ").at(0) == "curtask"){
        str.remove(0,8);
        if(str.size()==0)return;
        QStringList l = str.split(",");
        curTask.name = l[0];
        curTask.date = l[1];
        curTask.description = l[2];
        mytask->curTask = curTask;
        stack->setWindowTitle(curTask.name + " task");
        mytask->init();
        send("gettaskmember SELECT * FROM 'task_member' WHERE name = '"+curTask.name+"'");
    }
    //gettaskmember
    else if(str.split(" ").at(0) == "gettaskmember"){
        str.remove(0,14);
        send("gettaskcomment SELECT * FROM 'task_comment' WHERE task='"+curTask.name+"'");
        if(str.size()==0)return;
        QStringList l = str.split(" ");
        for(auto x:l){
            mytask->displayUser(User(x));
        }
    }
    //gettaskcomment
    else if(str.split(" ").at(0) == "gettaskcomment"){
        str.remove(0,16);
        QStringList l = str.split(",");
        if(str.size()==0)return;
        for(auto x:l){
            mytask->displayComment(x);
        }
    }
    //addmember
    else if(str == "addmember"){
        if(place == PLACE::about_organization) createAboutorganization();
        else if(place == PLACE::team) createTeam();
        else if(place == PLACE::project) createProject();
        else if(place == PLACE::task) createTask();
    }
    //removeteam || editteam
    else if(str == "removeteam" || str == "editteam"){
        auto com = dynamic_cast<QDialog*>(aboutmyteam->parent());
        com->close();
        createOrgan();
    }
    //removeproject || editproject
    else if(str == "removeproject" || str == "editproject"){
        auto com = dynamic_cast<QDialog*>(aboutmyproject->parent());
        com->close();
        createOrgan();
    }
    //getaboutteam
    else if(str.split(" ").at(0) == "getaboutteam"){
        str.remove(0,in);
        QStringList l = str.split(",");
        Team team;
        team.name = l[0];
        team.department = l[1];
        team.description = l[2];
        team.role = curOrgan.role;
        aboutmyteam->display(team);
    }
    //getaboutproject
    else if(str.split(" ").at(0) == "getaboutproject"){
        str.remove(0,in);
        QStringList l = str.split(",");
        Project project;
        project.name = l[0];
        project.goal = l[1];
        project.description = l[2];
        project.role = curOrgan.role;
        aboutmyproject->display(project);
    }
    //removememberproject
    else if(str == "removememberproject"){
        createProject();
    }
}
