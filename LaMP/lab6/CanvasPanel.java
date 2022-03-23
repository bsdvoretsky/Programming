import javax.swing.*;
import java.awt.*;

public class CanvasPanel extends JPanel {
    private int background;
    private int radius;

    public CanvasPanel() {
        background = 0;
        radius = 200;
    }

    public void setRadius(int r) {
        radius = r;
        repaint();
    }

    public void setBackground(int b) {
        background = b;
        repaint();
    }

    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        g.setColor(new Color(255, background, 0));
        g.fillArc(350 - radius, 250 - radius, 2 * radius, 2 * radius, 0, 360);
        g.setColor(Color.BLACK);

        g.fillArc(350 - radius / 2 - radius / 8 - (int)((double)background / 255 * radius / 8), 250 - radius / 4 - radius / 16 - (int)((double)background / 255 * 3 * radius / 16), radius / 4 + (int)((double)background / 255 * radius / 4), radius / 8 + (int)((double)background / 255 * 3 * radius / 8), 0, 360);
        g.fillArc(350 + radius / 4 + radius / 8 - (int)((double)background / 255 * radius / 8), 250 - radius / 4 - radius / 16 - (int)((double)background / 255 * 3 * radius / 16), radius / 4 + (int)((double)background / 255 * radius / 4), radius / 8 + (int)((double)background / 255 * 3 * radius / 8), 0, 360);

        g.drawLine(350 - radius / 2, 250 + radius / 2, 350, 250 + radius / 4 + (int)((double)background / 255 * radius / 2));
        g.drawLine(350, 250 + radius / 4 + (int)((double)background / 255 * radius / 2), 350 + radius / 2, 250 + radius / 2);

        g.drawLine(350 - radius / 2 - (int)((double)background / 255 * radius / 4), 250 - 3 * radius / 4 + (int)((double)background / 255 * radius / 4), 350 - radius / 4 - (int)((double)background / 255 * radius / 4), 250 - radius / 2 - (int)((double)background / 255 * radius / 4));
        g.drawLine(350 + radius / 4 + (int)((double)background / 255 * radius / 4), 250 - radius / 2 - (int)((double)background / 255 * radius / 4), 350 + radius / 2 + (int)((double)background / 255 * radius / 4), 250 - 3 * radius / 4 + (int)((double)background / 255 * radius / 4));
    }
}
