// a very basic Embedded HTTP Jersey server (supporting only GET/POST) in Java using just the Java SE API,
// without writing code to manually parse HTTP requests and manually format HTTP responses. 
// => com.sun.net.httpserver.HttpServer, we should be able to achieve all above.

//This file under package my.Jersey.Server.Java.tutorial
package my.Jersey.Server.Java.tutorial

/*TODO: 
- Add `Cross-origin resource sharing` to Web Jersey Application
- Convert project to Maven Project to simplify adding dependencies
- Add `jersey-server` dependency
- 
*/

import java.io.IOException;
import java.net.InetAddress;
import java.net.URI;
import java.net.UnknownHostException;

import java.ws.rs.core.UriBuilder;

import com.sun.jerset.api.container.httpserveer.HttpServerFactory;
import com.sun.jersey.api.core.PackagesResourceConfig;
import com.sun.jersey.api.core.ResourceConfig;
import com.sun.net.httpserver.HttpServer;
