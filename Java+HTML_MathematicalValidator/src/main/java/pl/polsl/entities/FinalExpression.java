package pl.polsl.entities;

/**
 * Class that contains final expression
 *   @since 5.0
 *   @author Sylwia Molitor
 *   @version 1.0
 */
public class FinalExpression {

    /**
     * id of the final expression
     */
    private int id;
    /**
     * expression with tags
     */
    private String expressionWithTags;
    /**
     * final expression
     */
    private String expressionAfterCorrection;

    /**
     * Constructor
     * @param id  id
     * @param expressionWithTags expression with tags
     * @param expressionAfterCorrection final expression
     */
    FinalExpression(int id, String expressionWithTags, String expressionAfterCorrection)
    {
        this.id = id;
        this.expressionWithTags = expressionWithTags;
        this.expressionAfterCorrection = expressionAfterCorrection;
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

    /**
     * Getter of the expression with tags
     * @return expression with tags
     */
    public String getExpressionWithTags() {
        return expressionWithTags;
    }

    /**
     * Setter of the expression with tags
     * @param expressionWithTags expression with tags
     */
    public void setExpressionWithTags(String expressionWithTags) {
        this.expressionWithTags = expressionWithTags;
    }

    /**
     * Getter of the final expression
     * @return final expression
     */
    public String getExpressionAfterCorrection() {
        return expressionAfterCorrection;
    }

    /**
     * Setter of the final expression
     * @param expressionAfterCorrection final expression
     */
    public void setExpressionAfterCorrection(String expressionAfterCorrection) {
        this.expressionAfterCorrection = expressionAfterCorrection;
    }
}
