package pl.polsl.controller;


import pl.polsl.entities.FinalExpression;
import pl.polsl.entities.InputExpression;
import pl.polsl.model.Model;
import pl.polsl.model.MyException;

import pl.polsl.view.ViewInternet;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.*;
import java.io.IOException;
import java.io.PrintWriter;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;


/**
 * pl.polsl.controller.Servlet
 *   @since 5.0
 *   @author Sylwia Molitor
 *   @version 3.0
 */
@WebServlet("/input")
public class Servlet extends HttpServlet {

    /**
     * Model on which we operate.
     */
    private final Model model = new Model();
    /**
     * ViewInternet on which we operate.
     */
    private final ViewInternet viewInternet = new ViewInternet();

    /**
     * doPost
     * @param request request
     * @param response response
     * @throws ServletException exception
     * @throws IOException exception
     */
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        try {
            processRequest(request, response);
        } catch (SQLException throwables) {
            throwables.printStackTrace();
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
    }

    /**
     * doGet
     * @param request request
     * @param response response
     * @throws ServletException exception
     * @throws IOException exception
     */
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        try {
            processRequest(request, response);
        } catch (SQLException throwables) {
            throwables.printStackTrace();
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
    }

    /**
     * processRequest used in doGet and doPost
     * @param request request
     * @param response response
     * @throws ServletException exception
     * @throws IOException exception
     * @throws SQLException exception
     * @throws ClassNotFoundException exception
     */
    public void processRequest( HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException, SQLException, ClassNotFoundException {


        PrintWriter out;
        out = response.getWriter();
        viewInternet.printBeginningOfHTML(out);
        String myText;
        response.setContentType("text/html");
        myText = request.getParameter("inputText");

        List<Table> allExpressions;
        HttpSession session = request.getSession(true);
        Object obj = session.getAttribute("allExpressions");

        if(obj == null)
        {
           allExpressions = new ArrayList<>();
        }
        else
        {
            allExpressions = (List<Table>) obj;
        }

            if (!myText.equals("")) {
                model.setExpressionBeforeCorrection(myText);
                model.setExpressionLength(myText.length());


                try {
                    model.throwSignException();
                } catch (MyException e) {
                    viewInternet.showExceptionInformation(out, false);
                    viewInternet.printEndOfHTML(out);
                    out.close();
                    return;
                }
                model.checkExpression(myText);
                //exception if there is dividing by zero
                try {
                    model.throwZeroException();
                } catch (MyException e) {
                    viewInternet.showExceptionInformation(out, true);
                    viewInternet.printEndOfHTML(out);
                    out.close();
                    return;
                }

                model.getInputTable().addExpression(request.getCookies().length, myText);


                if (model.getErrorStatus() != 0) {


                    if (model.getNumberOfWrongBrackets() != 0) {
                        viewInternet.showAdvice(out,2);
                    }if (model.getNumberOfSignErrors() > 0) {
                        viewInternet.showAdvice(out,1);
                    }
                    viewInternet.showNumberOfErrors(out, model.getNumberOfSignErrors(), model.getNumberOfWrongBrackets());
                }
                else
                {
                    viewInternet.printCorrectOrTheLackOfTheExpression(out, true);
                }
                Table newExpression = new Table(myText, model.getExpressionWithTags(), model.fixTheExpression());
                viewInternet.printExpression(out, newExpression);
                allExpressions.add(newExpression);
                request.getSession().setAttribute("allExpressions", allExpressions);
                Cookie cookieMaths = new Cookie(myText, model.fixTheExpression());
                response.addCookie(cookieMaths);

                model.getFinalTable().addExpression(request.getCookies().length, newExpression.getExpressionDuring(), newExpression.getExpressionAfter());

            } else
                viewInternet.printCorrectOrTheLackOfTheExpression(out, false);

        List<FinalExpression> finalToPrint=  model.getFinalTable().getAllExpressions();
        List<InputExpression> inputToPrint = model.getInputTable().getAllExpressions();
             viewInternet.printDatabase(out, inputToPrint, finalToPrint);


        viewInternet.printEndOfHTML(out);
        out.close();

    }




}

