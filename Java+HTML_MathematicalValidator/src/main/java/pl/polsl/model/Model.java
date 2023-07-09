package pl.polsl.model;


import pl.polsl.entities.TablefinalexpressionOperations;
import pl.polsl.entities.TableinputexpressionOperations;

import java.util.ArrayList;
import java.util.List;

import static java.lang.StrictMath.abs;

/**
 * Class Model
 *  @since 1.0
 *  @author Sylwia Molitor
 *  @version 5.0
 */
public class Model {

    /**
     * inputTable for database
     */
  private final TableinputexpressionOperations inputTable;
    /**
     * finalTable for database
     */
  private final TablefinalexpressionOperations finalTable;




    /**
     * Number of wrong brackets
     */
    private int numberOfWrongBrackets;


    /**
     * Input expression
     */
    private String expression;


    /**
     * Expression with tags
     */
    private String expressionWithTags;


    /**
     * Length of expression with tags
     */
    private int expressionWithTagsLength;


    /**
     * Length of input expression
     */
    private int expressionLength;

    /**
     * Getter of the TablefinalexpressionOperations
     * @return finalTable
     */
    public TablefinalexpressionOperations getFinalTable() {
        return finalTable;
    }

    /**
     * Getter of the TableinputexpressionOperations
     * @return inputTable
     */
    public TableinputexpressionOperations getInputTable() {
        return inputTable;
    }


    /**
     * Enum contains value that decides, which kind of error is in the program.
     */
    public enum ErrorCodes {
        /**
         * CORRECT_EXPRESSION means zero errors - it's the beginning value
         * NOT_CORRECT_EXPRESSION_$ means errors connected to signs like +,-,/,* etc and unacceptable signs
         * BRACKETS_ERROR means incorrectly matched brackets
         * BOTH_KINDS_OF_ERRORS means both kind of errors
         */
        CORRECT_EXPRESSION(0), NOT_CORRECT_EXPRESSION_$(1), BRACKETS_ERROR(2), BOTH_KINDS_OF_ERRORS(3);

        /**
         * number of error type
         */
        private int errorCode;

        /**
         * ErrorCodes constructor
         *
         * @param errorCode number of error type
         */
        ErrorCodes(int errorCode) {
            this.errorCode = errorCode;
        }

        /**
         * Setter of ErrorCode
         *
         * @param errorCode number of error type
         */
        public void setErrorCode(int errorCode) {
            this.errorCode = errorCode;
        }

        /**
         * Getter of ErrorCode
         *
         * @return errorCode number of error type
         */
        public int getErrorCode() {
            return errorCode;
        }
    }

    /**
     * Number of errors connected to signs
     */
    private int numberOfSignErrors;

    /**
     * errorStatus - object of the class ErrorCodes
     */
    private ErrorCodes errorStatus = ErrorCodes.CORRECT_EXPRESSION;


    /**
     * Getter of error type for Controller
     *
     * @return error type (number)
     */
    public int getErrorStatus() {
        return this.errorStatus.getErrorCode();
    }

    /**
     * Class constructor - at the beginning the expression is treated like a correct one.
     */
    public Model() {
        inputTable = new TableinputexpressionOperations();
        finalTable = new TablefinalexpressionOperations();
    }


    /**
     * Getter of the length of the expression.
     *
     * @return length of the expression.
     */
    public int getExpressionLength() {
        return expressionLength;
    }

    /**
     * Setter of the length of the expression.
     *
     * @param expressionLength length of the expression
     */
    public void setExpressionLength(int expressionLength) {
        this.expressionLength = expressionLength;
    }

    /**
     * Setter of the first expression.
     *
     * @param expressionBeforeCorrection user's expression
     */
    public void setExpressionBeforeCorrection(String expressionBeforeCorrection) {

        expression = expressionBeforeCorrection;
    }

    /**
     * Getter of the first expression.
     *
     * @return user's expression
     */
    public String getExpressionBeforeCorrection() {
        return expression;
    }

    /**
     * Setter of the errors specified below.
     *
     * @param numberOfSignErrors errors related to +,-,*,/,^, wrong symbols or ")(" instead of "()"
     */
    public void setNumberOfSignErrors(int numberOfSignErrors) {
        this.numberOfSignErrors = numberOfSignErrors;
    }

    /**
     * Getter of the errors specified below.
     *
     * @return number of errors related to +,-,*,/,^, wrong symbols or ")(" instead of "()".
     */
    public int getNumberOfSignErrors() {
        return numberOfSignErrors;
    }

    /**
     * Getter of the expression with "$" before an invalid symbol
     *
     * @return expression with "$" before an invalid symbol
     */
    public int getExpressionWithTagsLength() {
        return expressionWithTagsLength;
    }

    /**
     * Getter of a number of wrong brackets
     * if there is too many brackets, the value is positive, if not enough the value is negative, if there is correct amount of brackets the value equals zero
     *
     * @return number of wrong brackets
     */
    public int getNumberOfWrongBrackets() {
        return numberOfWrongBrackets;
    }

    /**
     * Setter of a number of wrong brackets
     * if there is too many brackets, the value is positive, if not enough the value is negative, if there is correct amount of brackets the value equals zero
     *
     * @param numberOfWrongBrackets number of wrong brackets
     */
    public void setNumberOfWrongBrackets(int numberOfWrongBrackets) {
        this.numberOfWrongBrackets = numberOfWrongBrackets;
    }

    /**
     * Setter of a expression length
     */
    public void setMathLength() {
        expressionWithTagsLength = expressionWithTags.length();
    }

    /**
     * Getter of a expression with "$"
     *
     * @return expression with "$"
     */
    public String getExpressionWithTags() {
        return expressionWithTags;
    }

    /**
     * Setter of a expression with "$"
     *
     * @param currentExpression expression with "$"
     */
    public void setExpressionWithTags(String currentExpression) { expressionWithTags = currentExpression;
    }


    /**
     * This method creates a new expression with "$" before wrong symbol.
     *
     * @param character         symbol from expression without "$"
     * @param errorInExpression true, if it's wrong symbol - add "$" false, if it's correct symbol - don't add anything
     */
    public void createExpressionWithTags(char character, boolean errorInExpression) {

       if(expressionWithTags != null)
       {
           if (errorInExpression) {
            expressionWithTags += "$";
            if (errorStatus.getErrorCode() == '0')
                errorStatus.setErrorCode(1);
            else
                errorStatus.setErrorCode(3);
        }
        expressionWithTags += character;
       }


    }

    /**
     * Throws exception connected to zero.
     * @throws MyException exception
     */
    public void throwZeroException() throws MyException
    {
        if(checkIfAnyDividingByZero())
            throw new MyException("EXCEPTION!!!");
    }

    /**
     * Throws exception connected to not allowed signs.
     * @throws MyException exception
     */
    public void throwSignException() throws MyException
    {
        if(checkIfNotAllowedSigns())
            throw new MyException();
    }

    /**
     * Method checks if in expression is division by zero.
     *
     * @return true if division by zero, false if there is not any division by zero
     */
    public boolean checkIfAnyDividingByZero() {

        if(expression != null) {
            List<Character> characters = new ArrayList<>();

            for (char ch : expression.toCharArray()) {
                characters.add(ch);
            }
            //char[] characters = expression.toCharArray();
            setExpressionLength(expression.length());

            for (int i = 0, j = 1; i < getExpressionLength() && j < getExpressionLength(); i++, j++) {
                if (characters.get(i) == '/' && characters.get(j) == '0')//found dividing
                {
                    if (j + 1 >= getExpressionLength())
                    {

                        return true;

                    }
                    if (j + 1 < getExpressionLength())
                        if (characters.get(j + 1) != '.')
                            return true;
                }
                if (characters.get(i) == '/' && characters.get(j) == '-')//found dividing
                {
                    if (j + 1 < getExpressionLength())
                        if (characters.get(j + 1) == '0')
                            return true;

                }

            }
            return false;

        }
        return false;
    }

    /**
     * Checks if in the expression were any '`', '#', '$', '@' that are used later.
     *
     * @return true if wrong expression, false if good expression
     */
    public boolean checkIfNotAllowedSigns() {

        if(expression != null) {
            List<Character> characters = new ArrayList<>();
            for (char ch : expression.toCharArray()) {
                characters.add(ch);
            }
            return characters.stream().anyMatch(n -> (n == '#' || n == '$' || n == '@' || n == '`'));
        }
        return false;
    }

    /**
     * Method checks if the expression has any errors connected to signs and brackets.
     *
     * @param mathematicalExpression input expression
     */
    public void checkExpression(String mathematicalExpression) {


        this.errorStatus.setErrorCode(0);
        boolean correctOrderOfBrackets = true;
        int numberOfBrackets = 0;
        int numberOfSquareBrackets = 0;
        boolean correctOrderOfSquareBrackets = true;
        int numberOfCurlyBrackets = 0;
        boolean correctOrderOfCurlyBrackets = true;
        int numberOfAbs = 0;

        setNumberOfSignErrors(0);
        setNumberOfWrongBrackets(0);
        setExpressionWithTags("");
        if(mathematicalExpression != null) { // char[] characters = mathematicalExpression.toCharArray();

            List<Character> characters = new ArrayList<>();

            for (char ch : mathematicalExpression.toCharArray()) {
                characters.add(ch);
            }

            for (int i = 0; i < getExpressionLength(); i++) {
                //not allowed letter
                if (characters.get(i) == 34 || characters.get(i) == 39 || characters.get(i) == 44 || characters.get(i) == 58 || characters.get(i) == 59 || characters.get(i) == 63 || characters.get(i) == 64 || characters.get(i) == 92 || characters.get(i) == 95 || characters.get(i) == 126) {
                    numberOfSignErrors++;
                    createExpressionWithTags(characters.get(i), true);
                    continue;
                }


                //number after letter
                if ((characters.get(i) > 96 && characters.get(i) < 123) || (characters.get(i) > 64 && characters.get(i) < 91)) {
                    if (i + 1 < getExpressionLength() && characters.get(i + 1) > 47 && characters.get(i + 1) < 58) {
                        numberOfSignErrors++;
                        createExpressionWithTags(characters.get(i), true);
                        continue;
                    }
                }
                //check before the sign
                if (characters.get(i) == '+' || characters.get(i) == '-' || characters.get(i) == '/' || characters.get(i) == '*' || characters.get(i) == '^' || characters.get(i) == '%' || characters.get(i) == '=' || characters.get(i) == '<' || characters.get(i) == '>' || characters.get(i) == '!') {

                    if (i == 0 && characters.get(i) != '-' && characters.get(i) != '!') {
                        numberOfSignErrors++;
                        createExpressionWithTags(characters.get(i), true);
                        continue;

                    }

                    if (i > 0) {
                        if (!(characters.get(i - 1) == '|' || (characters.get(i - 1) == '}') || (characters.get(i - 1) == ']') || (characters.get(i - 1) == ')') || (characters.get(i - 1) > 47 && characters.get(i - 1) < 58) || (characters.get(i - 1) > 96 && characters.get(i - 1) < 123) || (characters.get(i - 1) > 64 && characters.get(i - 1) < 91))) //letters and numbers
                        {

                            if (characters.get(i - 1) != 32 && ((characters.get(i) != '-' || characters.get(i - 1) == '-'))) {
                                numberOfSignErrors++;
                                createExpressionWithTags(characters.get(i), true);
                                continue;

                            }
                        }
                    }
                    if (i + 1 == getExpressionLength()) {
                        numberOfSignErrors++;
                        createExpressionWithTags(characters.get(i), true);
                        continue;
                    } else {
                        if ((characters.get(i + 1) == '}') || (characters.get(i + 1) == ']') || (characters.get(i + 1) == ')')) {
                            numberOfSignErrors++;
                            createExpressionWithTags(characters.get(i), true);
                            continue;
                        }
                    }

                }
                //check the left bracket '('
                if (characters.get(i) == '(') {
                    numberOfBrackets++;
                    if (numberOfBrackets > 0) {
                        correctOrderOfBrackets = true;
                    }
                }
                //check the right bracket ')'
                if (characters.get(i) == ')') {

                    numberOfBrackets--;
                    if (numberOfBrackets < 0) {
                        correctOrderOfBrackets = false;
                        createExpressionWithTags(characters.get(i), true);
                        continue;

                    }
                }
                //check the left bracket '['
                if (characters.get(i) == '[') {
                    numberOfSquareBrackets++;
                    if (numberOfSquareBrackets > 0) {
                        correctOrderOfSquareBrackets = true;
                    }
                }
                //check the right bracket ']'
                if (characters.get(i) == ']') {
                    numberOfSquareBrackets--;
                    if (numberOfSquareBrackets < 0) {
                        correctOrderOfSquareBrackets = false;
                        createExpressionWithTags(characters.get(i), true);
                        continue;

                    }
                }
                //check the left bracket '{'
                if (characters.get(i) == '{') {
                    numberOfCurlyBrackets++;
                    if (numberOfCurlyBrackets > 0) {
                        correctOrderOfCurlyBrackets = true;
                    }
                }
                //check the right bracket '}'
                if (characters.get(i) == '}') {
                    numberOfCurlyBrackets--;
                    if (numberOfCurlyBrackets < 0) {
                        correctOrderOfCurlyBrackets = false;
                        createExpressionWithTags(characters.get(i), true);
                        continue;

                    }
                }
                //check absolute value signs
                if (characters.get(i) == '|') {
                    numberOfAbs++;
                }


                //check the fraction
                if (characters.get(i) == '.') {
                    if (i + 1 < getExpressionLength() && i > 0) {
                        if (!((characters.get(i - 1) > 47 && characters.get(i - 1) < 58) && (characters.get(i + 1) > 47 && characters.get(i + 1) < 58))) {
                            numberOfSignErrors++;
                            createExpressionWithTags(characters.get(i), true);
                            continue;
                        }
                    } else {
                        numberOfSignErrors++;
                        createExpressionWithTags(characters.get(i), true);
                        continue;
                    }
                }
                createExpressionWithTags(characters.get(i), false);


            }

            //add '#' in places where brackets are missing
            if (numberOfBrackets != 0) {
                for (int i = 0; i < numberOfBrackets; i++) {
                    expressionWithTags += "#";
                }

            }
            //add '`' in places where square brackets are missing
            if (numberOfSquareBrackets != 0) {
                for (int i = 0; i < numberOfSquareBrackets; i++) {
                    expressionWithTags += "`";
                }
            }
            //add '@' in places where curly brackets are missing
            if (numberOfCurlyBrackets != 0) {

                for (int i = 0; i < numberOfCurlyBrackets; i++) {
                    expressionWithTags += "@";
                }
            }
            //abs
            if (numberOfAbs % 2 == 1) {
                numberOfSignErrors++;
                expressionWithTags += "|";
            }


            // count errors connected to the brackets
            if (!correctOrderOfBrackets)
                numberOfSignErrors++;
            if (!correctOrderOfSquareBrackets)
                numberOfSignErrors++;
            if (!correctOrderOfCurlyBrackets)
                numberOfSignErrors++;
            int totalBracketsErrors = abs(numberOfBrackets) + abs(numberOfSquareBrackets) + abs(numberOfCurlyBrackets);
            if (totalBracketsErrors > 0) {
                if (errorStatus.getErrorCode() == '0')
                    errorStatus.setErrorCode(2);
                else
                    errorStatus.setErrorCode(3);
            }
            setNumberOfWrongBrackets(totalBracketsErrors);
            setMathLength();
        }
    }


    /**
     * Method fixes signs in input expression.
     *
     * @return fixed expression
     */
    public String fixTheExpression() {

        if(expressionWithTags != null)
        //List<Character> characters = Collections.synchronizedList(new ArrayList<Character>());
        {
            List<Character> characters = new ArrayList<>();
            for (char ch : expressionWithTags.toCharArray()) {
                characters.add(ch);
            }
            //char[] characters = expressionWithTags.toCharArray();
            expression = "";
            setMathLength();
            for (int i = 0; i < getExpressionWithTagsLength(); i++) {
                if (characters.get(i) == '$') {
                    i++;
                } else if (characters.get(i) == '#') {
                    expression += ')';
                } else if (characters.get(i) == '`') {
                    expression += ']';
                } else if (characters.get(i) == '@') {
                    expression += '}';
                } else {
                    expression += characters.get(i);
                }

            }
        }
        return expression;
    }
}