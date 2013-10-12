package wikiflix.project;

import java.io.IOException;
import java.io.PrintWriter;
import java.net.URL;
import javax.servlet.http.*;
import com.google.appengine.api.urlfetch.HTTPHeader;
import com.google.appengine.api.urlfetch.HTTPMethod;
import com.google.appengine.api.urlfetch.HTTPRequest;
import com.google.appengine.api.urlfetch.HTTPResponse;
import com.google.appengine.api.urlfetch.URLFetchService;
import com.google.appengine.api.urlfetch.URLFetchServiceFactory;

@SuppressWarnings("serial")
public class Wiki_FlixServlet extends HttpServlet {
	public void doGet(HttpServletRequest req, HttpServletResponse resp)
			throws IOException {
		resp.setContentType("application/json");
		PrintWriter pw = resp.getWriter();
            URL url = new URL("http://api.themoviedb.org/3/movie/now_playing?api_key=64a2409beb376d93795786427e4de2a6");
    		HTTPRequest request = new HTTPRequest(url, HTTPMethod.GET);//, options);
    		request.setHeader(new HTTPHeader("Accept", "application/json"));
    		
    		
    		URLFetchService urlFetch = URLFetchServiceFactory.getURLFetchService();	
    	
    		HTTPResponse response = urlFetch.fetch(request);
    		
    		byte[] arrResponseContent = response.getContent();
    		pw.print(new String(arrResponseContent));
}
}
