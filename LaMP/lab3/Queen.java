package com.company;

public class Queen implements Comparable<Queen> {
    public int pos_x, pos_y;
    public Queen(char x, int y) {
        this.pos_x = (int) x - 97;
        this.pos_y = y - 1;
        Chessboard.setQueen(this.pos_y, this.pos_x);
    }
    public int compareTo(Queen obj) {
        return Integer.compare(Chessboard.countHits(obj.pos_x, obj.pos_y), Chessboard.countHits(this.pos_x, this.pos_y));
    }
    public String toString() {
        return (char) (this.pos_x + 97) + ":" + (this.pos_y + 1);
    }
}
