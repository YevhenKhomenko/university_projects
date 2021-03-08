package com.da72;
import java.util.LinkedList;
import java.util.Queue;

class CPUQueue {
     private Queue<String> queue = new LinkedList<>();
     private static int queueCount = 1;
     private static int deletedProcesses = 0;
     private int capacity;
     private CPUProcess cpuProc;
     private CPU cpu;
     private CPUQueue newQueue;
     private int maxSize;
     private boolean reachedMaxSize = false;

     public CPUQueue(int capacity, CPUProcess cpuProc, CPU cpu,int maxSize) {
         this.capacity = capacity;
         this.cpuProc = cpuProc;
         this.cpu = cpu;
         this.maxSize = maxSize;
         System.out.println("New queue has been created, size : " + queue.size());
     }

    public void setMaxSize(int maxSize) {
        this.maxSize = maxSize;
    }

    public static int getQueueCount() {
        return queueCount;
    }

    public synchronized void put(String element) throws InterruptedException {
         /*
         Если очередь заполнена, создаем новый обьект CPUQueue , передаем его
         потоку CPUProcess, чтобы новые процессы записывались уже в новую очередь
          */
         if(queue.size() == capacity) {
             System.out.println("Queue is FULL, creating new queue..");

             newQueue = new CPUQueue(capacity, cpuProc, cpu, maxSize);
             cpuProc.setNewProcessQueue(newQueue);
             reachedMaxSize = true;
             queueCount++;
             wait();

         }
         queue.add(element);
         System.out.println("Process added, queue size = [" + queue.size() + "]\n");
         notify(); // notifyAll() for multiple CPU/CPUProcess threads
     }

     public synchronized String get() throws InterruptedException {
         /*
            передаем новую очередь на обработку процессору
          */
         if ((queue.size() == 1) && (reachedMaxSize == true)){   // wait()  не нужно тк поток CPUProcess уже освободил
                                                                 // эту очередь(перешел к нoвой)
             cpu.setNewCpuQueue(newQueue);
             //wait();
         }
         /*
            Если размер очереди превышает заданный размер, содержимое очереди поступает на обработку в процессор
            В ином случае - ждем
          */
         while((reachedMaxSize == false)&&(queue.isEmpty() || (queue.size() <= maxSize))) {
             System.out.println("Queue is not ready, waiting..");
             wait();
         }
         String item = queue.remove();
         deletedProcesses++;
         System.out.println("Process removed, queue size = [" + queue.size() + "]"+" proc num: "+deletedProcesses);

         notify(); // notifyAll() for multiple CPU/CPUProcess threads
         return item;
     }
}
