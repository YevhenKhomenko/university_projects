package com.da72;

import java.io.IOException;
import java.util.Random;

/** Поток-вычислитель группы ячеек */
class MultiplierThread extends Thread
{
    private final int[] vector;
    private final int[][] matrix;
    private final int[] resultVector;
    private final int firstIndex;
    private final int lastIndex;
    private final int sumLength;


    public MultiplierThread(final int[] vector,
                            final int[][] matrix,
                            final int[] resultVector,
                            final int firstIndex,
                            final int lastIndex)
    {
        this.vector  = vector;
        this.matrix = matrix;
        this.resultVector = resultVector;
        this.firstIndex   = firstIndex;
        this.lastIndex    = lastIndex;

        sumLength = vector.length;
    }

    /**Вычисление значения в одной ячейке.*/
    private void calcValue( final int idx)
    {
        int sum = 0;
        for (int i = 0; i < sumLength; ++i)
            sum += vector[i] * matrix[i][idx];
        resultVector[idx] = sum;
    }

    /** Рабочая функция потока. */
    @Override
    public void run()
    {
        System.out.println("Thread " + getName() + " started. Calculating cells from " + firstIndex + " to " + lastIndex + "...");

        final int vLen = vector.length;
        for (int index = firstIndex; index < lastIndex; ++index)
            calcValue(index);

        System.out.println("Thread " + getName() + " finished.");
    }
}

class Main
{

    /** Заполнение матрицы случайными числами.
     */
    private static void randomMatrix(final int[][] matrix)
    {
        final Random random = new Random();

        for (int row = 0; row < matrix.length; ++row)
            for (int col = 0; col < matrix[row].length; ++col)
                matrix[row][col] = random.nextInt(100);
    }

    private static void randomVector(final int[] vector)
    {
        final Random random = new Random();

        for (int idx = 0; idx < vector.length; ++idx)
                vector[idx] = random.nextInt(100);
    }

    private static void printVector(int[] vector){
        for(int i =  0; i < vector.length; i++){
            System.out.print(vector[i]);
        }
        System.out.println();
    }


    /** Однопоточное умножение.*/
    private static int[] multiply(final int[] vector,
                                          final int[][] matrix)
    {
        final int vLen = vector.length;
        final int colCount = vector.length;
        final int[] result = new int[vLen];

        for (int idx = 0; idx < vLen; ++idx) {

                int sum = 0;
                for (int i = 0; i < vLen; ++i) {
                    sum += vector[i] * matrix[i][idx];
                }
                result[idx] = sum;

        }

        return result;
    }

    /** Многопоточное умножение.*/
    private static int[] multiplyMT(final int[] vector,
                                            final int[][] matrix,
                                            int threadCount)
    {
        assert threadCount > 0;

        final int vLength = vector.length;      // Длина результирующего вектора.
        final int[] result = new int[vLength];  // Результирующий вектор.

        final int cellsForThread = vLength / threadCount;  // Число вычисляемых ячеек на поток.
        int firstIndex = 0;  // Индекс первой вычисляемой ячейки.
        final MultiplierThread[] multiplierThreads = new MultiplierThread[threadCount];  // Массив потоков.

        // Создание и запуск потоков.
        long timeMT = System.currentTimeMillis();
        for (int threadIndex = threadCount - 1; threadIndex >= 0; --threadIndex) {
            int lastIndex = firstIndex + cellsForThread;  // Индекс последней вычисляемой ячейки.
            if (threadIndex == 0) {
                /* Один из потоков вычисляет  и остаток, если число ячеек не делится нацело на число потоков. */
                lastIndex = vLength;
            }
            multiplierThreads[threadIndex] = new MultiplierThread(vector, matrix, result, firstIndex, lastIndex);
            multiplierThreads[threadIndex].start();
            firstIndex = lastIndex;
        }

        // Ожидание завершения потоков.
        try {
            for (final MultiplierThread multiplierThread : multiplierThreads)
                multiplierThread.join();
        }
        catch (InterruptedException e) {
            e.printStackTrace();
        }
        long parallelTime = System.currentTimeMillis() - timeMT;
        System.out.println( "Время работы многопоточного расчета: " + parallelTime);
        return result;
    }

    /** Длина вектора. */
    final static int N_DIM  = 20000 ;//10000
    /** Число потоков. */
    final  static int THREAD_NUM = 8;//Runtime.getRuntime().availableProcessors()*2;



    public static void main(String[] args)
    {
        final int[] vector  = new int[N_DIM];
        final int[][] matrix = new int[N_DIM][N_DIM];


        randomVector(vector);
        randomMatrix(matrix);
        final int[] resultVectorMT = multiplyMT(vector, matrix, THREAD_NUM);
        //System.out.println((int)Runtime.getRuntime().availableProcessors());

        long time = System.currentTimeMillis();
        final int[] resultVector = multiply(vector, matrix);
        time = System.currentTimeMillis() - time;
        System.out.println( "Время работы однопоточного расчета: " + time);
        //acceleration = time/parallelTime;
        //System.out.println("Ускорение: "+acceleration);
        //printVector(resultVectorMT);
        //printVector(resultVector);

        // Проверка многопоточных вычислений с помощью однопоточных.
        for (int idx = 0; idx < N_DIM; ++idx) {
                if (resultVectorMT[idx] != resultVector[idx]) {
                    System.out.println("Error in multithreaded calculation!");
                    return;
                }
        }

    }
}