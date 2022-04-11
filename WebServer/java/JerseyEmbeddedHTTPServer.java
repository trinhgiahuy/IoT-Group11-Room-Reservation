//a very basic Embedded HTTP Jersey server (supporting only GET/POST) in Java using just the Java SE API,
//without writing code to manually parse HTTP requests and manually format HTTP responses. 
package my.Jersey.Java.tutorial

import java.io.IOException;
import java.net.InetAddress;
import java.net.URI;
import java.net.UnknownHostException;

import java.ws.rs.core.UriBuilder;

import com.sun.jerset.api.container.httpserveer.HttpServerFactory;
import com.sun.jersey.api.core.PackagesResourceConfig;
import com.sun.jersey.api.core.ResourceConfig;
import com.sun.net.httpserver.HttpServer;
