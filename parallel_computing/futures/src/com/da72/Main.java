package com.da72;
import java.util.*;
import java.util.concurrent.CompletableFuture;
import java.util.concurrent.ExecutionException;

public class Main {
    public static void main(String[] args) {
        final List<Integer> a1 = new LinkedList<>( Arrays.asList(0,9,6,2,5,1,7,4,3,8)); //first
        final List<Integer> a2 = new LinkedList<>( Arrays.asList(8,7,0,1,3,6,9,2,5,4)); //second
        CompletableFuture <List<Integer>> firstFuture, secondFuture, resultFuture;

        /*
          supplyAsync() и thenApplyAsync() выполняются в разных,отличных от главного,
          потококах полученных из глобального ForkJoinPool.commonPool()
          thenApplyAsync() - callback метод, вызывающийся при получении future
         */
        firstFuture = CompletableFuture.supplyAsync(() -> a1).thenApplyAsync(first -> {
            first.removeIf((e) -> e <= 0.7 * Collections.max(first));// передаем предикат методу removeIf()
            Collections.sort(first);
            return first;
        });
        /*

         */
        secondFuture = CompletableFuture.supplyAsync(() -> a2).thenApplyAsync(second -> {
            second.removeIf((e) -> e % 3 != 0);
            Collections.sort(second);
            return second;
        });

        /*Может выполняться в главном потоке */
        resultFuture = firstFuture.thenCombine(secondFuture, (first,second) -> {
            List a3 = new ArrayList<>(second);
            a3.removeAll(first);
            Collections.sort(a3);
            return a3;
        });
        /*Тут главный поток блокируется до завершения resultFuture */
        try {
            System.out.println("Result: " + resultFuture.get());
        } catch (InterruptedException e) {
            e.printStackTrace();
        } catch (ExecutionException e) {
            e.printStackTrace();
        }
    }
}
