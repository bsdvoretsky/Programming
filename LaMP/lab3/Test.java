package com.company;
import java.util.Arrays;

public class Test {

    public static void main(String[] args) {
        Chessboard chessboard = new Chessboard();
        Queen[] queens = new Queen[] {
                new Queen('a', 8),
                new Queen('e', 8),
                new Queen('c', 6),
                new Queen('h', 6),
                new Queen('e', 4),
                new Queen('a', 1),
                new Queen('e', 1),
                new Queen('h', 1)

        };
        Arrays.sort(queens);
        for (Queen queen : queens) System.out.println(queen.toString());
    }
}
