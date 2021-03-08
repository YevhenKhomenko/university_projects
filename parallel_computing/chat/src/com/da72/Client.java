import java.io.IOException;
import java.net.Socket;

public class Client {

    protected Connection connection;
    private volatile boolean clientConnected = false;



    public static void main(String[] args) {

        Client client = new Client();
        client.run();
    }


    public void run() {

        // Создаем новый сокетный поток с помощью метода getSocketThread
        SocketThread socketThread = getSocketThread();
        // Помечаем созданный поток как daemon для того, чтобы при выходе
        // из программы вспомогательный поток прервался автоматически.
        socketThread.setDaemon(true);
        // Запускаем вспомогательный поток
        socketThread.start();

        // Заставляем текущий поток ожидать, пока он не получит нотификацию из другого потока
        try {
            synchronized (this) {
                this.wait();
            }
        } catch (InterruptedException e) {
            ConsoleHelper.writeMessage("Ошибка");
            return;
        }

        //После того, как поток дождался нотификации, проверяем значение clientConnected
        if (clientConnected) {
            ConsoleHelper.writeMessage("Соединение установлено. Для выхода наберите команду 'exit'.");

            //Считываем сообщения с консоли пока клиент подключен. Если будет введена команда 'exit', то выходим из цикла
            while (clientConnected) {
                String message;
                if (!(message = ConsoleHelper.readString()).equals("exit")) {
                    if (shouldSentTextFromConsole()) {
                        sendTextMessage(message);
                    }
                } else {
                    return;
                }
            }
        }
        else {
            ConsoleHelper.writeMessage("Произошла ошибка во время работы клиента.");
        }
    }


    protected String getServerAddress() {

        ConsoleHelper.writeMessage("Введите адрес сервера: ");
        return ConsoleHelper.readString();
    }

    protected int getServerPort() {

        ConsoleHelper.writeMessage("Введите порт сервера: ");
        return ConsoleHelper.readInt();
    }

    protected String getUserName() {

        ConsoleHelper.writeMessage("Введите имя пользователя: ");
        return ConsoleHelper.readString();
    }

    protected boolean shouldSentTextFromConsole() {

        return true;
    }


    /* создает и возвращает новый объект класса SocketThread */
    protected SocketThread getSocketThread() {

        return new SocketThread();
    }


    /*  создает новое текстовое сообщение, используя переданный текст и отправляет его серверу через соединение connection */
    protected void sendTextMessage(String text) {

        try {
            connection.send(new Message(MessageType.TEXT, text));

        } catch (IOException e) {
            ConsoleHelper.writeMessage("Ошибка отправки");
            clientConnected = false;
        }
    }



    public class SocketThread extends Thread {


        public void run() {

            try {
                // Создаем новый объект класса java.net.Socket c запросом сервера и порта
                Socket socket = new Socket(getServerAddress(), getServerPort());

                // Создаем объект класса Connection, используя сокет
                Client.this.connection = new Connection(socket);


                clientHandshake();
                clientMainLoop();


            } catch (IOException e) {
                notifyConnectionStatusChanged(false);
            } catch (ClassNotFoundException e) {
                notifyConnectionStatusChanged(false);
            }

        }


        /* метод реализовывает главный цикл обработки сообщений сервера */
        protected void clientMainLoop() throws IOException, ClassNotFoundException {

            while (true) {

                // В цикле получаем сообщения, используя соединение connection
                Message message = connection.receive();

                switch (message.getType()) {

                    case TEXT:
                        processIncomingMessage(message.getData());
                        break;

                    case USER_ADDED:
                        informAboutAddingNewUser(message.getData());
                        break;

                    case USER_REMOVED:
                        informAboutDeletingNewUser(message.getData());
                        break;

                    default:
                        throw new IOException("Unexpected MessageType");
                }
            }
        }


        /** clientHandshake **/
        protected void clientHandshake() throws IOException, ClassNotFoundException {

            while (true) {

                // В цикле получаем сообщения, используя соединение connection
                Message message = connection.receive();

                switch (message.getType()) {

                    // 	Если тип полученного сообщения NAME_REQUEST (сервер запросил имя)
                    case NAME_REQUEST: {

                        // запрашиваем ввод имени пользователя с помощью метода getUserName()
                        // и отправляем сообщение серверу.
                        String userName = getUserName();
                        connection.send(new Message(MessageType.USER_NAME, userName));
                        break;
                    }

                    // Если тип полученного сообщения NAME_ACCEPTED (сервер принял имя)
                    case NAME_ACCEPTED: {

                        // значит сервер принял имя клиента, нужно об этом сообщить главному потоку
                        notifyConnectionStatusChanged(true);
                        return;
                    }

                    default: {
                        throw new IOException("Unexpected MessageType");
                    }
                }
            }
        }



        protected void processIncomingMessage(String message) {
            ConsoleHelper.writeMessage(message);
        }



        protected void informAboutAddingNewUser(String userName) {
            ConsoleHelper.writeMessage("участник " + userName + " присоединился к чату");
        }



        protected void informAboutDeletingNewUser(String userName) {
            ConsoleHelper.writeMessage("участник " + userName + " покинул чат");
        }


        /*
         Устанавливаем значение поля clientConnected класса Client
         Оповещаем (пробуждаем ожидающий) основной поток класса Client
         */
        protected void notifyConnectionStatusChanged(boolean clientConnected) {


            Client.this.clientConnected = clientConnected;

            synchronized (Client.this) {
                Client.this.notify();
            }
        }
    }
}
