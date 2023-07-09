package pl.polsl.model;


import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;
import org.junit.jupiter.params.provider.ValueSource;

import java.util.stream.Stream;

import static org.junit.jupiter.api.Assertions.*;

/**
 * Class for testing
 *   @since 2.0
 *   @author Sylwia Molitor
 *   @version 3.0
 */

class ModelTest {

    /**
     * Used in testCreateExpressionWithTags
     * @return returns stream of character and errorInExpression
     */
    private static Stream<Arguments> testCreateExpressionWithTags() {
        return Stream.of(
                Arguments.of('a', true),
                Arguments.of('+', true),
                Arguments.of('b', true),
                Arguments.of('2', false),
                Arguments.of('7', false),
                Arguments.of('1', false)
        );
    }

    /**
     * Tests creating expression with tags - if the output value is correct
     * @param character added sign
     * @param errorInExpression adds "$" and character if true, only character if false
     */
    @ParameterizedTest
    @MethodSource
    void testCreateExpressionWithTags(char character, boolean errorInExpression) {
        try{

            Model object = new Model();
            object.setExpressionWithTags("");
            object.createExpressionWithTags(character, errorInExpression);

            assertEquals(errorInExpression, object.getExpressionWithTags().contains("$"), "The expression was created not correctly!"); //it will always be good

        }
        catch (Exception e)
        {
           fail();
        }
    }

    /**
     * Used in testCheckExpression
     * @return stream of testedExpression, numberOfWrongSings, numberOfWrongBrackets
     */
    private static Stream<Arguments> testCheckExpression() {
        return Stream.of(
                Arguments.of("2+2", 0,0),
                Arguments.of("1=1", 0,0),
                Arguments.of("/", 1,0),
                Arguments.of("k=2*1", 0,0),
                Arguments.of("(", 0,1),
                Arguments.of("2++18", 1,0),
                Arguments.of("(-2)", 0,0),
                Arguments.of("2-+(-2)", 1,0));
    }

    /**
     * Tests if the testedExpression is correct(signs, brackets), if it's incorrect or the expression was null/empty
     * @param testedExpression input expression
     * @param numberOfWrongBrackets number of wrong brackets
     * @param numberOfWrongSings number of wrong signs
     */
    @ParameterizedTest
    @MethodSource
    void testCheckExpression(String testedExpression, int numberOfWrongSings, int numberOfWrongBrackets) {
        try{
            Model object = new Model();
            object.setExpressionLength(testedExpression.length());
            object.setNumberOfWrongBrackets(0);
            object.setNumberOfSignErrors(0);
            object.checkExpression(testedExpression);
            assertEquals(numberOfWrongSings, object.getNumberOfSignErrors(), "There were sign errors!");
            assertEquals(numberOfWrongBrackets, object.getNumberOfWrongBrackets(), "There were bracket errors!");

        }
        catch (Exception e)
        {
            fail();
        }

    }

    /**
     * Fixes the expression and checks if it was done correctly, if the expression was null/empty or done incorrectly
     * @param testedExpression input expression
     */
    @ParameterizedTest
    @ValueSource(strings = {"29+1","(4+4@", "2+$+2", "{9/1@", "[2*1`"})
    void testFixTheExpression(String testedExpression) {
       try{

            Model object = new Model();
            object.setExpressionWithTags(testedExpression);
            String test = object.fixTheExpression();
            assertFalse(test.contains("$") || test.contains("`") || test.contains("#") || test.contains("@"), "Expression was wrongly fixed!");

       }
        catch (Exception e)
        {
            fail();
        }

    }

    /**
     * Used in testCheckIfNotAllowedSigns
     * @return stream of testedExpression and boolean if there were not allowed signs
     */
    private static Stream<Arguments> testCheckIfNotAllowedSigns() {
        return Stream.of(
                Arguments.of("29+1", false),
                Arguments.of("#+1", true),
                Arguments.of("44", false),
                Arguments.of("1`22", true),
                Arguments.of("@", true),
                Arguments.of("$$", true));
    }
    /**
     * Tests if in expression were any not allowed signs (`,$,#,@) or the expression was null/empty
     * @param testedExpression input expression
     * @param notAllowedSigns true if there were not allowed signs
     */
    @ParameterizedTest
    @MethodSource
    void testCheckIfNotAllowedSigns(String testedExpression, boolean notAllowedSigns) {
        try{
            Model object = new Model();
            object.setExpressionBeforeCorrection(testedExpression);
            boolean test = object.checkIfNotAllowedSigns();
            assertEquals(notAllowedSigns, test, "There were not allowed signs there!");
          }
        catch (Exception e)
        {
            fail();
        }
    }


    /**
     * Used in testCheckIfAnyDividingByZero
     * @return stream of testedExpression and boolean if there was division by zero
     */
    private static Stream<Arguments> testCheckIfAnyDividingByZero() {
        return Stream.of(
                Arguments.of("29+1", false),
                Arguments.of("2/0", true),
                Arguments.of("44", false),
                Arguments.of("22/1", false),
                Arguments.of("8/0", true),
                Arguments.of("2+0", false),
                Arguments.of("9/0.99", false),
                Arguments.of("1/-0", true));
    }
    /**
     * Tests if in expression was any dividing by zero or the expression was null/empty
     * @param testedExpression input expression
     * @param divisionByZero true if there was division by zero, false otherwise
     */

    @ParameterizedTest
    @MethodSource
    void testCheckIfAnyDividingByZero(String testedExpression, boolean divisionByZero) {
        try{
            Model object = new Model();
            object.setExpressionBeforeCorrection(testedExpression);
            boolean test = object.checkIfAnyDividingByZero();
            assertEquals(divisionByZero,test, "There was dividing by zero!");
          }
        catch (Exception e)
        {
            fail();
        }
    }

}