import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

public class Server {

    /* ключ -имя клиента, а значение - соединение с ним */
    private static Map<String, Connection> connectionMap = new ConcurrentHashMap<>();


    public static void main(String[] args) throws IOException {

        ConsoleHelper.writeMessage("Введите порт сервера: ");
        int serverPort = ConsoleHelper.readInt();

        try (ServerSocket serverSocket = new ServerSocket(serverPort)) {

            ConsoleHelper.writeMessage("Сервер запущен");

            while (true) {
                //Слушаем
                Socket socket = serverSocket.accept();
                Handler handler = new Handler(socket);
                //запускаем handler
                handler.start();
            }
        }

    }


    /* отправка сообщения для всех */
    public static void sendBroadcastMessage(Message message) {

        try {

            for (Connection connection : connectionMap.values()) {
                connection.send(message);
            }

        } catch (Exception e){
            e.printStackTrace();
            ConsoleHelper.writeMessage("Сообщение не отправлено");
        }

    }


    /*обработчик, в котором будет происходить обмен сообщениями с клиентом */
    private static class Handler extends Thread {

        private Socket socket;

        public Handler(Socket socket) {

            this.socket = socket;
        }


        @Override
        public void run() {

            ConsoleHelper.writeMessage("Установленно соединение с адресом " + socket.getRemoteSocketAddress());
            String clientName = null;
            //Создаем Connection
            try (Connection connection = new Connection(socket)) {
                //Выводим сообщение, что установлено новое соединение с удаленным адресом
                ConsoleHelper.writeMessage("Подключение к порту: " + connection.getRemoteSocketAddress());
                //Вызываем метод, реализующий рукопожатие с клиентом, сохраняя имя нового клиента
                clientName = serverHandshake(connection);
                //Рассылаем всем участникам чата информацию об имени присоединившегося участника (сообщение с типом USER_ADDED)
                sendBroadcastMessage(new Message(MessageType.USER_ADDED, clientName));
                //Сообщаем новому участнику о существующих участниках
                sendListOfUsers(connection, clientName);
                //Запускаем главный цикл обработки сообщений сервером
                serverMainLoop(connection, clientName);


            } catch (IOException e) {
                ConsoleHelper.writeMessage("Ошибка при обмене данными с удаленным адресом");
            } catch (ClassNotFoundException e) {
                ConsoleHelper.writeMessage("Ошибка при обмене данными с удаленным адресом");
            }

            //После того как все исключения обработаны, удаляем запись из connectionMap
            connectionMap.remove(clientName);
            //и отправлялем сообщение остальным пользователям
            sendBroadcastMessage(new Message(MessageType.USER_REMOVED, clientName));

            ConsoleHelper.writeMessage("Соединение с удаленным адресом закрыто");

        }

        /** Handshake **/
        private String serverHandshake(Connection connection) throws IOException, ClassNotFoundException {

            while (true) {
                // Формируем и отправляем команду запроса имени пользователя
                connection.send(new Message(MessageType.NAME_REQUEST));
                // Получаем ответ клиента
                Message message = connection.receive();

                // Проверяем, что получена команда с именем пользователя
                if (message.getType() == MessageType.USER_NAME) {

                    //Достаем из ответа имя, проверяем, что оно не пустое
                    if (message.getData() != null && !message.getData().isEmpty()) {

                        // и пользователь с таким именем еще не подключен
                        if (connectionMap.get(message.getData()) == null) {

                            // Добавим нового пользователя и соединение с ним в connectionMap
                            connectionMap.put(message.getData(), connection);
                            // Отправим клиенту команду информирующую, что его имя принято
                            connection.send(new Message(MessageType.NAME_ACCEPTED));

                            // Вернуть принятое имя в качестве возвращаемого значения
                            return message.getData();
                        }
                    }
                }
            }
        }


        /* Отправка списка всех пользователей */
        private void sendListOfUsers(Connection connection, String userName) throws IOException {

            for (String key : connectionMap.keySet()) {
                Message message = new Message(MessageType.USER_ADDED, key);

                if (!key.equals(userName)) {
                    connection.send(message);
                }
            }
        }


        /** Главный цикл обработки сообщений сервером **/
        private void serverMainLoop(Connection connection, String userName) throws IOException, ClassNotFoundException {

            while (true) {

                Message message = connection.receive();
                // Если принятое сообщение – это текст (тип TEXT)
                if (message.getType() == MessageType.TEXT) {

                    String s = userName + ": " + message.getData();

                    Message formattedMessage = new Message(MessageType.TEXT, s);
                    sendBroadcastMessage(formattedMessage);
                } else {
                    ConsoleHelper.writeMessage("Error");
                }
            }
        }
    }
}
