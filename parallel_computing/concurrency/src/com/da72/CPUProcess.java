package com.da72;

public class CPUProcess implements Runnable {
    private CPUQueue queue;
    private int generateNumber;



    CPUProcess(int gN){
        this.generateNumber = gN;
    }
    public void setNewProcessQueue(CPUQueue newQueue){
        this.queue = newQueue;

    }

    public void run(){
        long generateDelay;
        for (int i = 0; i < generateNumber; i++) {
            int randMin = 10;
            int randMax = 20; // rand = [10,50]

            generateDelay = randMin + (int) (Math.random() * randMax);
            try {
                Thread.sleep(generateDelay);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            try {
                System.out.println("Process generated with delay" + generateDelay + " proc num : "+ i);
                queue.put("New process");
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        queue.setMaxSize(-1); // чтобы процессор смог обработать полностью последнюю очередь
        System.out.println("No more processes. Queue number is " + CPUQueue.getQueueCount());
    }
}
