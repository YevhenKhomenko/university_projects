package com.da72;

public class CPU implements Runnable {
    CPUQueue queue;

    CPU(){

    }

    public void setNewCpuQueue(CPUQueue newQueue) {
        System.out.println("New queue has been connected to CPU");
        this.queue = newQueue;
        //System.out.println("is new queue empty : = "+ queue.isEmpty() );
        //System.out.println("Q size: "+ queue.getSize());
    }

    public void run(){
        long processingTime;
        while(true) {
            int randMin = 20;
            int randMax = 40; // rand = [20,100]
            processingTime = randMin + (int) (Math.random() * randMax);

            try {
                queue.get();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

            System.out.println("CPU: Processed in time " + processingTime + "\n");
            try {
                Thread.sleep(processingTime);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
