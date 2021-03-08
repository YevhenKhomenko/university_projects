package com.da72;

import java.util.Arrays;
import java.util.OptionalInt;
import java.util.OptionalLong;
import java.util.concurrent.ForkJoinPool;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.atomic.AtomicLong;
import java.util.stream.IntStream;
import java.util.Random;
import java.util.stream.LongStream;

public class Main {

    static int sum = 0;
    static int count = 0;
    static int controlSum = 0;
    static long maxElem;
    static long minElem;
    static int SIZE = 5000000;

    public static void main(String[] args) {

        //int array[] = new int [SIZE];
        //Arrays.fill(array,2);
        int array[] =  new Random().ints(SIZE,0,100000).toArray();
        long longArray[] =  new Random().longs(SIZE,0,100000).toArray();

        AtomicInteger atomicSum = new AtomicInteger(); /*створення атомарної змінної (atomic variable)*/
        int serialSum = IntStream.of(array).sum();

        IntStream.of(array).parallel().forEach( arrayElement -> {
            /*вбудований метод для виконання паралельних обчислень у Java*/
            sum += arrayElement; /*знаходження суми без використання
            атомарної змінної*/
            int oldValue;
            int newValue;
            do { //зміна суми з використанням методу compareAndSet
                oldValue = atomicSum.get();
                newValue = oldValue + arrayElement;
            } while(!atomicSum.compareAndSet(oldValue , newValue));
        });
        System.out.println(ForkJoinPool.getCommonPoolParallelism() + 1);
        System.out.println("Serial sum: " + serialSum);
        System.out.println("Blocking sum: " + sum);
        System.out.println("Atomic sum: " + atomicSum.get());

        findElementCount(array);
        findControlSum(array);
        findMaxElement(longArray);
        findMinElem(longArray);
    }

    /* знаходження кiлькостi елемнтiв в масивi типу int */
    public static void findElementCount(int array[]){

        AtomicInteger atomicCount = new AtomicInteger();
        int serialCount = (int) IntStream.of(array).count();
        IntStream.of(array).parallel().forEach( arrayElement -> {  /*вбудований метод для виконання паралельних обчислень у Java*/
            count += 1; /*знаходження кiлькостi без використання атомарної змінної*/
            int oldValue;
            int newValue;
            do {
                oldValue = atomicCount.get();
                newValue = oldValue + 1;
            } while(!atomicCount.compareAndSet(oldValue , newValue));
        });
        System.out.println("///////////////////////////////");
        System.out.println("Serial count: " + serialCount);
        System.out.println("Blocking count: " + count);
        System.out.println("Atomic count: " + atomicCount.get());
    }

    public static void findMinElem(long array[]){
        AtomicLong atomicMinElem = new AtomicLong();
        OptionalLong serialMinElem = LongStream.of(array).min();
        LongStream.of(array).parallel().forEach(arrayElement -> {
            if (arrayElement < minElem) {
                minElem = arrayElement;
            }
            long oldValue;
            long newValue;
            do {
                oldValue = atomicMinElem.get();
                if (arrayElement < oldValue) {
                    newValue = arrayElement;
                } else {
                    break;
                }
            } while (!atomicMinElem.compareAndSet(oldValue, newValue));

        });
        System.out.println("///////////////////////////////");
        if(serialMinElem.isPresent()) {
            System.out.println("Serial min number: " + serialMinElem.getAsLong());
        }else {
            System.out.println("No value");
        }
        System.out.println("Blocking min number: " + maxElem);
        System.out.println("Atomic min number: " + atomicMinElem.get());
        System.out.println("Min number index: " + findIndex(array,atomicMinElem));
    }

    public static void findMaxElement(long array[]) {
        AtomicLong atomicMaxElem = new AtomicLong();
        OptionalLong serialMaxElem = LongStream.of(array).max();
        LongStream.of(array).parallel().forEach(arrayElement -> {
            if (arrayElement > maxElem) {
                maxElem = arrayElement;
            }
            long oldValue;
            long newValue;
            do {
                oldValue = atomicMaxElem.get();
                if (arrayElement > oldValue) {
                    newValue = arrayElement;
                } else {
                    break;
                }
            } while (!atomicMaxElem.compareAndSet(oldValue, newValue));

        });
        System.out.println("///////////////////////////////");
        if(serialMaxElem.isPresent()) {
            System.out.println("Serial max number: " + serialMaxElem.getAsLong());
        }else {
            System.out.println("No value");
        }
        System.out.println("Blocking max number: " + maxElem);
        System.out.println("Atomic max number: " + atomicMaxElem.get());
        System.out.println("Max number index: " + findIndex(array,atomicMaxElem));
    }

    public static void findControlSum(int array[]){
        AtomicInteger atomicControlSum = new AtomicInteger();
        OptionalInt serialControlSum = IntStream.of(array).reduce((a, b) -> (a ^ b));
        IntStream.of(array).parallel().forEach( arrayElement -> {
            controlSum ^= arrayElement;
            int oldValue;
            int newValue;
            do {
                oldValue = atomicControlSum.get();
                newValue = oldValue ^ arrayElement;
            } while(!atomicControlSum.compareAndSet(oldValue , newValue));
        });

        System.out.println("///////////////////////////////");
        if(serialControlSum.isPresent()) {
            System.out.println("Serial control sum: " + serialControlSum.getAsInt());
        }else {
            System.out.println("No value");
        }
        System.out.println("Blocking control sum: " + controlSum);
        System.out.println("Atomic control sum: " + atomicControlSum.get());
    }


    public static long findIndex(long[] array, AtomicLong target)
    {
        return IntStream.range(0, array.length)
                .filter(i -> target.get() == array[i])
                .findFirst()
                .orElse(-1);	// return -1 if target is not found
    }
}
