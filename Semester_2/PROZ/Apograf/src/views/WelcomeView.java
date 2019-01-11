package views;


import javax.swing.*;
import java.awt.*;


/**
 * Class from View part of MVC model of programming in Java. Contains welcoming components shown
 * after logging into the program. Class inherits from Window.
 * @see Window
 */
public class WelcomeView extends views.Window {

    /**
     * Constructor of this view class, initialising JLabels and setting their layout on the screen.
     */
    public WelcomeView(){

        JLabel welcomeLabel = new javax.swing.JLabel();
        JLabel actionLabel = new javax.swing.JLabel();
        JLabel signature = new javax.swing.JLabel();

        welcomeLabel.setText("WELCOME TO APOGRAF APP!");
        welcomeLabel.setHorizontalAlignment(SwingConstants.CENTER);
        welcomeLabel.setFont(new Font("Comic Sans MS", Font.PLAIN, 80));
        welcomeLabel.setForeground(Color.blue);

        actionLabel.setText("You can choose your action in menu bar above. I wish you good attendance checking!");
        actionLabel.setHorizontalAlignment(SwingConstants.CENTER);
        actionLabel.setFont(new Font("Times New Roman", Font.PLAIN, 40));

        signature.setText("Wojciech Sitek");
        signature.setHorizontalAlignment(SwingConstants.CENTER);
        signature.setFont(new Font("Times New Roman", Font.ITALIC, 35));

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
                layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                        .addGroup(layout.createSequentialGroup()
                                .addComponent(welcomeLabel, javax.swing.GroupLayout.PREFERRED_SIZE, 1241, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addGap(0, 0, Short.MAX_VALUE))
                        .addGroup(layout.createSequentialGroup()
                                .addContainerGap()
                                .addComponent(actionLabel, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                                .addContainerGap())
                        .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                                .addComponent(signature, javax.swing.GroupLayout.PREFERRED_SIZE, 298, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addGap(487, 487, 487))
        );
        layout.setVerticalGroup(
                layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                        .addGroup(layout.createSequentialGroup()
                                .addComponent(welcomeLabel, javax.swing.GroupLayout.PREFERRED_SIZE, 221, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addGap(101, 101, 101)
                                .addComponent(actionLabel, javax.swing.GroupLayout.PREFERRED_SIZE, 137, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addGap(18, 18, 18)
                                .addComponent(signature, javax.swing.GroupLayout.PREFERRED_SIZE, 66, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addContainerGap(299, Short.MAX_VALUE))
        );
        setVisible(true);
    }
}
