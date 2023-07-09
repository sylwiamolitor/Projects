package pl.polsl.controller;

import pl.polsl.view.ViewInternet;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.List;

/**
 * ServletWithHistory of previous entered expressions.
 * pl.polsl.controller.ServletWithHistory
 *   @since 6.0
 *   @author Sylwia Molitor
 *   @version 1.0
 */
@WebServlet("/previousInput")
public class ServletWithHistory extends HttpServlet {
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
        processRequest(request, response);
    }

    /**
     * doGet
     * @param request request
     * @param response response
     * @throws ServletException exception
     * @throws IOException exception
     */
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        processRequest(request, response);
    }

    /**
     * processRequest used in doGet and doPost
     * @param request request
     * @param response response
     * @throws ServletException exception
     * @throws IOException exception
     */
    public void processRequest( HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException{

        PrintWriter out;
        response.setContentType("text/html");
        out = response.getWriter();
        viewInternet.printBeginningOfHTML(out);

        if(request.getSession().getAttribute("allExpressions") != null) {
            List<Table> allExpressions = (List<Table>) request.getSession().getAttribute("allExpressions");
            viewInternet.printAllExpressions(out, allExpressions);
        }

        Cookie[] ck =request.getCookies();
        viewInternet.printAllCookies(out, ck);
        viewInternet.printEndOfHTML(out);
        out.close();
    }
}
