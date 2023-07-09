package pl.polsl.controller;


/**
 * Class for table in graphics application.
 *  @since 5.0
 *  @author Sylwia Molitor
 *  @version 1.0
 */
public class Table {

    /**
     * Expression in first column - input expression.
     */
    private String expressionBefore;
    /**
     * Expression in second column - expression with tags.
     */
    private String expressionDuring;
    /**
     * Expression in third column - expression after correction.
     */
    private String expressionAfter;


    /**
     * Constructor of Table.
     * @param expressionBefore input expression
     * @param expressionDuring expression with tags
     * @param expressionAfter  expression after correction
     */
    public Table(String expressionBefore, String expressionDuring, String expressionAfter) {
        super();
        this.expressionBefore = expressionBefore;
        this.expressionDuring = expressionDuring;
        this.expressionAfter = expressionAfter;
    }

    /**
     * Getter of an input expression.
     * @return input expression
     */
    public String getExpressionBefore() {

        return expressionBefore;
    }

    /**
     * Getter of an expression after correction
     * @return expression after correction
     */
    public String getExpressionAfter() {

        return expressionAfter;
    }

    /**
     * Getter of an expression with tags
     * @return expression with tags
     */
    public String getExpressionDuring() {
        return expressionDuring;
    }

    /**
     * Setter of an input expression.
     * @param inputExpressionBefore input expression
     */
    public void setExpressionBefore(String inputExpressionBefore) {
        this.expressionBefore = inputExpressionBefore;
    }

    /**
     * Setter of an expression after correction
     * @param inputExpressionAfter expression after correction
     */
    public void setExpressionAfter(String inputExpressionAfter) {
       this.expressionAfter = inputExpressionAfter;
    }

    /**
     * Setter of an expression with tags
     * @param inputExpressionDuring expression with tags
     */
    public void setExpressionDuring(String inputExpressionDuring) {
        this.expressionDuring = inputExpressionDuring;
    }

}
