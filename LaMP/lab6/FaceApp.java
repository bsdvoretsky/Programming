import javax.swing.*;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import java.awt.*;

public class FaceApp {
    private JFrame frame;
    private JSpinner radiusSpinner;
    private JSlider faceSlider;
    private CanvasPanel canvasPanel;

    public FaceApp() {
        createFrame();
        initElements();
    }

    public void createFrame() {
        frame = new JFrame("FaceApp");
        frame.setSize(700, 700);
        frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
    }

    public void show() {
        frame.setVisible(true);
    }

    private void initElements() {
        Container mainContainer = frame.getContentPane();
        mainContainer.setLayout(new BorderLayout());
        Box bottomPanel = createBottomPanel();

        canvasPanel = new CanvasPanel();
        canvasPanel.setBackground(Color.BLACK);
        mainContainer.add(canvasPanel, BorderLayout.CENTER);
        mainContainer.add(bottomPanel, BorderLayout.SOUTH);
        radiusSpinner.setValue(200);
        faceSlider.setValue(0);
    }

    private Box createBottomPanel() {
        Box panel = Box.createVerticalBox();
        panel.add(Box.createVerticalStrut(20));
        panel.add(Box.createHorizontalStrut(200));

        JLabel radiusLabel = new JLabel("Радиус");
        panel.add(radiusLabel);

        panel.add(Box.createVerticalStrut(20));

        radiusSpinner = new JSpinner();
        radiusSpinner.setMaximumSize(new Dimension(300, 30));
        radiusSpinner.addChangeListener(new ChangeListener() {
            @Override
            public void stateChanged(ChangeEvent e) {
                radiusSpinner.setValue(Math.abs((int)radiusSpinner.getValue() % 225));
                canvasPanel.setRadius((int)radiusSpinner.getValue());
            }
        });
        panel.add(radiusSpinner);

        panel.add(Box.createVerticalStrut(20));

        faceSlider = new JSlider();
        faceSlider.setMinimum(0);
        faceSlider.setMaximum(255);
        faceSlider.addChangeListener(new ChangeListener() {
            @Override
            public void stateChanged(ChangeEvent e) {
                canvasPanel.setBackground(faceSlider.getValue());
            }
        });
        faceSlider.setMaximumSize(new Dimension(300, 30));
        panel.add(faceSlider);
        panel.add(Box.createVerticalStrut(20));
        return panel;
    }
}
