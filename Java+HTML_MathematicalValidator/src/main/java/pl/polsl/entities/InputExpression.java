package pl.polsl.entities;


/**
 * Class that contains input expression
 *   @since 5.0
 *   @author Sylwia Molitor
 *   @version 1.0
 */
public class InputExpression {

    /**
     * id of the expression
     */
    private int id;
    /**
     * input expression
     */
    private String inputExpression;

    /**
     * Constructor
     * @param id id of the expression
     * @param inputExpression   input expression
     */
    public InputExpression(int id, String inputExpression) {
        this.id = id;
        this.inputExpression = inputExpression;
    }

    /**
     * Getter of the input expression
     * @return input expression
     */
    public String getInputExpression() {
        return inputExpression;
    }

    /**
     * Setter of the input expression
     * @param inputExpression input expression
     */
    public void setInputExpression(String inputExpression) {
        this.inputExpression = inputExpression;
    }

    /**
     * Getter of the id
     * @return id
     */
    public int getId() {
        return id;
    }

    /**
     * Setter of the id
     * @param id id
     */
    public void setId(int id) {
        this.id = id;
    }
}
