package com.company;
import java.util.Arrays;

public class Test {

    public static void main(String[] args) {
	    Sequence[] sequences = new Sequence[]{
                new Sequence(),
                new Sequence(),
                new Sequence(),
                new Sequence()
        };
        Arrays.sort(sequences);
        for (Sequence s : sequences) System.out.println(s.toString());
    }
}
