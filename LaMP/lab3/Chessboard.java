package com.company;

public class Chessboard {
    public static boolean[][] chessboard;
    public Chessboard() {
        chessboard = new boolean[8][8];
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                chessboard[i][j] = false;
            }
        }
    }
    public static void setQueen (int i, int j) {
        chessboard[i][j] = true;
    }
    public static int countHits(int x, int y) {
        int c = -1;
        int fl;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (chessboard[i][j]) {
                    fl = 0;
                    if (i == y) {
                        for (int k = Math.min(x, j) + 1; k < Math.max(x, j); k++) {
                            if (chessboard[i][k]) {
                                fl = 1;
                                break;
                            }
                        }
                        if (fl == 0) {
                            fl = 2;
                        }
                    } else if (j == x) {
                        for (int k = Math.min(y, i) + 1; k < Math.max(y, i); k++) {
                            if (chessboard[k][j]) {
                                fl = 1;
                                break;
                            }
                        }
                        if (fl == 0) {
                            fl = 2;
                        }
                    } else if (Math.abs(y - i) == Math.abs(x - j)) {
                        int k = y;
                        int q = x;
                        if (k < i && q < j) {
                            while (k < i && q < j) {
                                k++;
                                q++;
                                if (k < i && q < j && chessboard[k][q]) {
                                    fl = 1;
                                    break;
                                }
                            }
                            if (fl == 0) {
                                fl = 2;
                            }
                        } else if (k < i && q > j) {
                            while (k < i && q > j) {
                                k++;
                                q--;
                                if (k < i && q > j && chessboard[k][q]) {
                                    fl = 1;
                                    break;
                                }
                            }
                            if (fl == 0) {
                                fl = 2;
                            }
                        } else if (k > i && q < j) {
                            while (k > i && q < j) {
                                k--;
                                q++;
                                if (k > i && q < j && chessboard[k][q]) {
                                    fl = 1;
                                    break;
                                }
                            }
                            if (fl == 0) {
                                fl = 2;
                            }
                        } else if (k > i && q > j) {
                            while (k > i && q > j) {
                                k--;
                                q--;
                                if (k > i && q > j && chessboard[k][q]) {
                                    fl = 1;
                                    break;
                                }
                            }
                            if (fl == 0) {
                                fl = 2;
                            }
                        }
                    }
                    if (fl == 2) {
                        c++;
                    }
                }
            }
        }
        return c;
    }
}
