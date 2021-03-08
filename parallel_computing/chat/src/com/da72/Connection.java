
import java.io.Closeable;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.net.SocketAddress;

/*
Класс Connection выполняет роль обвертки над классом
java.net.Socket, которая умеет сериализовать и десериализовать объекты
типа Message в сокет. Методы этого класса готовы к вызову из разных
потоков.
 */


public class Connection implements Closeable {

    private final Socket socket;
    private final ObjectOutputStream out;
    private final ObjectInputStream in;


   /*
    Создаем объект класса ObjectOutputStream до того, как будет создаваться объект
    класса ObjectInputStream, иначе может возникнуть взаимная блокировка потоков,
    которые хотят установить соединение через класс Connection.
    */
    public Connection(Socket socket) throws IOException {
        this.socket = socket;
        this.out = new ObjectOutputStream(socket.getOutputStream());
        this.in = new ObjectInputStream(socket.getInputStream());
    }


    public void send(Message message) throws IOException {

        synchronized (out) {
            out.writeObject(message);
            out.flush();

        }

    }


    public Message receive() throws IOException, ClassNotFoundException {

        Message message;

        synchronized (in) {
            message = (Message)in.readObject();
            return message;
        }

    }


    public SocketAddress getRemoteSocketAddress() {

        return socket.getRemoteSocketAddress();
    }


    public void close() throws IOException {

        in.close();
        out.close();
        socket.close();
    }

}