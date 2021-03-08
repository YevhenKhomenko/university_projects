package com.da72;

public class Main {

    /*
        capacity - количество мест в очередях
        maxSize - размер очереди , превышение которого запускает работу процессора
        processToGenerate - количество процессов, которое должно быть сгенерировано
     */
    public static void main(String[] args) {
        int queueCapacity = 5;
        int maxSize = 3;
        int processToGenerate = 100;

        System.out.println("\nQueue capacity = [" + queueCapacity + "], will be generated " + processToGenerate + " processes\n");

        CPUProcess Cp = new CPUProcess(processToGenerate);
        CPU C = new CPU();
        CPUQueue q = new CPUQueue(queueCapacity, Cp, C, maxSize );
        Cp.setNewProcessQueue(q);
        C.setNewCpuQueue(q);

        new Thread(Cp).start();
        new Thread(C).start();
    }
}
