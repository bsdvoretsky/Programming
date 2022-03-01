package com.company;

public class Sequence implements Comparable<Sequence>{
    public int[] sequence;
    public int getRandomNumber(int min, int max) {
        return (int) ((Math.random() * (max - min)) + min);
    }
    public static int countPeaks(int[] sequence) {
        int c = 0;
        for (int i = 0; i < sequence.length; i++) {
            if (((i - 1 >= 0) && (i + 1 < sequence.length) && (sequence[i - 1] <= sequence[i]) && (sequence[i + 1] <= sequence[i])) || ((i == 0) && (sequence[i] >= sequence[i + 1])) || ((i == sequence.length - 1) && (sequence[i] >= sequence[i - 1]))) {
                c++;
            }
        }
        return c;
    }
    public Sequence() {
        this.sequence = new int[getRandomNumber(2, 10)];
        for (int i = 0; i < this.sequence.length; i++) {
            this.sequence[i] = getRandomNumber(-1000, 1000);
        }
    }

    public int compareTo(Sequence obj) {
        return Integer.compare(Sequence.countPeaks(obj.sequence), Sequence.countPeaks(this.sequence));
    }

    public String toString() {
        StringBuilder s = new StringBuilder();
        for (int i = 0; i < this.sequence.length - 1; i++) {
            s.append(Integer.toString(this.sequence[i]));
            s.append(", ");
        }
        s.append(Integer.toString(this.sequence[this.sequence.length - 1]));
        return s.toString();
    }
}
