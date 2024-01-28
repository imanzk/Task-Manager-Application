#include "mainwindow.h"

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
            file.close();
            createHome();
            send("client "+curUser.username);
        }
    }else create(com_type::entrance);

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
    if(socket)
    {
        if(socket->isOpen())
        {
            QDataStream socketStream(socket);
            socketStream.setVersion(QDataStream::Qt_5_15);

            QByteArray header;
            header.prepend(QString("fileType:message,fileName:null,fileSize:%1;").arg(str.size()).toUtf8());
            header.resize(128);

            QByteArray byteArray = str.toUtf8();
            byteArray.prepend(header);

            socketStream << byteArray;
        }
        else
            qDebug("Socket doesn't seem to be opened");
    }
    else
        qDebug("Not connected");
}

void MainWindow::create(com_type type){
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
    hom = new home;
    stack->setWindowTitle("Home");
    connect(hom , &home::_click , this , &MainWindow::homFunc);
    stack->addWidget(hom);
    stack->setCurrentWidget(hom);
    stack->show();
}

void MainWindow::createCreateorgan()
{
    stack->setEnabled(false);
    QDialog *dialog = new QDialog();
    createorgan = new createorganization(dialog);
    dialog->move(pos() + (QGuiApplication::primaryScreen()->geometry().center() - geometry().center()));
    dialog->show();
    connect(dialog,&QDialog::finished , [&](){stack->setEnabled(true);});
    connect(createorgan,&createorganization::_click , this , &MainWindow::createorganFunc);
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
            send("client "+curUser.username);
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

    }
    else if(t == HOME::logout){
        QDir dir;
        QString path = dir.path() + "/user.txt";
        QFile file(path);
        file.remove();
        exit(0);
    }else if(t == HOME::organclick){

    }
    else if(t == HOME::sort){

    }else if(t == HOME::tasks){

    }
}

void MainWindow::createorganFunc(Organization org)
{
    send("org INSERT INTO organization (name, type, description) VALUES ('"+org.name+"','"+org.type+"','"+org.description+"')");
    curOrgan = org;
}

void MainWindow::get(QString str){
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
        send("SELECT username "+curUser.username);
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
    }

}







