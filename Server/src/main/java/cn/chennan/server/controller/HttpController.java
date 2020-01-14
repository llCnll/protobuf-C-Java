package cn.chennan.server.controller;

import cn.chennan.server.proto.Http;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.util.List;

/**
 * @author ChenNan
 * @date 2020-01-13 下午6:39
 **/
@Controller
public class HttpController {

    @RequestMapping(value = "http")
    @ResponseBody
    public String http(HttpServletRequest request, HttpServletResponse response) throws Exception {

        Http.PointCloud pointCloud = Http.PointCloud.parseFrom(request.getInputStream());
        System.out.println(pointCloud.getTotal());
        List<Http.Point3f> map = pointCloud.getMapPointsList();
        map.forEach(point ->{
            System.out.println(String.format("(%f, %f, %f)", point.getX(), point.getY(), point.getZ()));
        });

//        Http.Point3f p1 = Http.Point3f.parseFrom(request.getInputStream());
//        System.out.println(String.format("(%f, %f, %f)", p1.getX(), p1.getY(), p1.getZ()));

        /*Http.Point3f.Builder builder = Http.Point3f.newBuilder();
        builder.setX(100f).setY(200f).setZ(300f);

        Http.Point3f resp = builder.build();
        System.out.println(resp.toString());

        byte[] buff = resp.toByteArray();
        response.setContentType("application/x-protobuf");
        response.getOutputStream().write( buff );   // 发送*/

        return "ok";
    }

}
