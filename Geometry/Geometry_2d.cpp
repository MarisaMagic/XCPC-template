#include <bits/stdc++.h>
using namespace std;

#define ios ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)


namespace Geo {
    template<typename T>
    class Point;    // 点

    template<typename T>
    class Line;     // 线

    template<typename T>
    class Polygon;  // 多边形

    template<typename T>
    class Circle;   // 圆

    template<typename T>
    using Vector = Point<T>;     // 向量
    
    template<typename T>
    using Segment = Line<T>;     // 线段
    
    template<typename T>
    using PointSet = Polygon<T>; // 点集

    const double eps = 1e-8;      // 误差 
    const double PI = acos(-1.0); // pai, 3.1415926...

    // 判断数值正负
    template<typename T>
    int sgn(T x){ 
        if(abs(x) < eps) return 0; // 等于0
        return x > 0 ? 1 : -1; // 1: 正数，2: 负数
    }

    template<typename T>
    int cmp(T x, T y){ // 比较两个数
        if(abs(x - y) < eps) return 0; // x == y，返回 0
        return x < y ? -1 : 1; // x < y，返回 -1; x > y，返回 1
    }

    // 角度转弧度
    double radians(double deg){ return deg * PI / 180.0; }

    // 两点之间的距离（需要 operator-, operator*）
    template<typename T>
    double dist(const Point<T>& A, const Point<T>& B){ return (double)sqrt((A - B) * (A - B)); }

    // 两点之间的距离平方（需要 operator-, operator*）
    template<typename T>
    T dist2(const Point<T>& A, const Point<T>& B){ return (A - B) * (A - B); }

    // 向量的模（长度，需要 operator*）
    template<typename T>
    double len(const Vector<T>& A){ return (double)sqrt(A * A); }

    // 向量的模平方（长度，需要 operator*）
    template<typename T>
    T len2(const Vector<T>& A){ return A * A; }

    // 两个向量的点积（内积，dot，需要 operator*）
    // \vec a \cdot \vec b = |a||b|\cos{\theata}
    // \theata: \vec a 旋转到 \vec b 经过的夹角
    template<typename T>
    T dot(const Vector<T>& A, const Vector<T>& B){ return A * B; }

    // 两个向量的叉积（cross，需要 operator^）
    // \vec a \cdot \vec b = |a||b|\sin{\theata}
    // \theata: \vec a 旋转到 \vec b 经过的夹角
    template<typename T>
    T cross(const Vector<T>& A, const Vector<T>& B){ return A ^ B; }

    // 两个向量的夹角（弧度制）
    template<typename T>
    double angle(const Vector<T>& A, const Vector<T>& B){ 
        return acos(dot(A, B) / len(A) / len(B)); // [0, pi]
    }

    // 两个向量的 A -> B 的 逆时针 夹角（弧度制）
    template<typename T>
    double angle2(const Vector<T>& A, const Vector<T>& B){
        // 值域范围 [0, 2 * pi]
        double res = atan2(B.y, B.x) - atan2(A.y, A.x);
        return res >= 0 ? res : res + 2 * PI;
    }

    // 两个向量的夹角（角度制）
    template<typename T>
    double angle_deg(const Vector<T>& A, const Vector<T>& B){
        return angle(A, B) * (180 / PI); // [0, 180]
    }

    // 单位向量
    template<typename T>
    Vector<T> unit_vector(const Vector<T>& A){ return A / len(A); }

    // 向量旋转（弧度制）
    // 逆时针旋转 rad: rotate(A, rad)
    // 顺时针旋转 rad: rotate(A, -rad)
    template<typename T>
    Vector<T> rotate(const Vector<T>& A, double rad){
        return Vector(A.x * cos(rad) - A.y * sin(rad), A.x * sin(rad) + A.y * cos(rad));
    }

    // 两个向量构成平行四边形有向面积，输入三点ABC
    // 得到向量 AB 和 AC，A为公共点，B、C点需逆时针输入
    template<typename T>
    T area_parallelogram(const Point<T>& A, const Point<T>& B, const Point<T>& C){
        return cross(B - A, C - A);
    }

    // 两个有公共点的向量 A 和 B 构成平行四边形有向面积
    // 向量 A 和 B 需要逆时针输入
    template<typename T>
    T area_parallelogram(const Vector<T>& A, const Vector<T>& B){
        return cross(A, B);
    }

    // 两个向量构成三角形有向面积，输入三点ABC
    // 得到向量 AB 和 AC，A为公共点，B、C点需逆时针输入
    template<typename T>
    double area_triangle(const Point<T>& A, const Point<T>& B, const Point<T>& C){
        return cross(B - A, C - A) / 2.0;
    }

    // 两个有公共点的向量 A 和 B 构成三角形有向面积
    // 向量 A 和 B 需要逆时针输入
    template<typename T>
    double area_triangle(const Vector<T>& A, const Vector<T>& B){
        return cross(A, B) / 2.0;
    }

    // 点 p 与直线 v: s -> t 的位置关系。
    // 1: p 在 s -> t 左侧
    // 2: 在 s -> t 右侧，
    // 0: 在 s -> t 上 
    template<typename T>
    int relation_point_line(const Point<T>& p, const Line<T>& v){
        int c = sgn(cross(p - v.s, v.t - v.s));
        if(c < 0) return 1;
        if(c > 0) return 2;
        return 0;
    }

    // 点 p 与线段 v: s - t 的位置关系
    // 0: p 不在线段上
    // 1: p 在线段上
    template<typename T>
    bool relation_point_segment(const Point<T>& p, const Segment<T>& v){
        // 夹角为0 并且 与两端点形成平角（< 0 不包括端点）
        return sgn(cross(p - v.s, v.t - v.s)) == 0 && sgn(dot(p - v.s, p - v.t) <= 0);
    }

    // 点 p 到直线 v: s -> t 距离
    template<typename T>
    double dist_point_line(const Point<T>& p, const Line<T>& v){
        // 向量 s -> p 和 s -> t 构成平行四边形无向面积除以底长度
        return abs(area_parallelogram(p - v.s, v.t - v.s)) / len(v.t - v.s);
    }

    // 点 p 在直线 v: s -> t 的投影
    template<typename T>
    Point<T> proj_point_line(const Point<T>& p, const Line<T>& v){
        double k = dot(p - v.s, v.t - v.s) / len2(v.t - v.s);
        return v.s + (v.t - v.s) * k;
    }

    // 点 p 关于直线 v: s -> t 的对称点
    template<typename T>
    Point<T> symm_point_line(const Point<T>& p, const Line<T>& v){
        Point<T> q = proj_point_line(p, v);
        return Point<T>(2 * q.x - p.x, 2 * q.y - p.y);
    }

    // 点 p 到线段 v: s - t 的距离
    // 若 p 到 s->t 投影不再线段上，即与一点夹角大于90，取到端点距离最小值
    template<typename T>
    double dist_point_segment(const Point<T>& p, const Segment<T>& v){
        if(sgn(dot(p - v.s, v.t - v.s)) < 0 || sgn(dot(p - v.t, v.s - v.t)) < 0){
            return min(dist(p, v.s), dist(p, v.t));
        }
        return dist_point_line(p, v);
    }

    // 两个向量是否平行或重合
    template<typename T>
    bool parallel_vector_vector(const Vector<T>& A, const Vector<T>& B) {
        return sgn(cross(A, B)) == 0;
    }

    // 两个向量 v1 和 v2 的关系
    // 0: 两向量共线
    // 1: v2 在 v1 的逆时针方向
    // 2: v2 在 v1 的顺时针方向
    template<typename T>
    int relation_vector_vector(const Vector<T>& v1, const Vector<T>& v2){
        int c = sgn(cross(v1, v2));
        if(c == 0) return 0;
        if(c > 0) return 1;
        return 2;
    }

    // 两条直线的位置关系
    // 0: 平行
    // 1: 重合
    // 2: 相交
    template<typename T>
    int relation_line_line(const Line<T>& v1, const Line<T>& v2){
        if(sgn(cross(v1.t - v1.s, v2.t - v2.s)) == 0){
            if(relation_point_line(v1.s, v2) == 0) return 1;
            return 0;
        }
        return 2;
    }

    // 两个向量的夹角类型
    // 0: 夹角为 0
    // 1: 夹角为锐角
    // 2: 夹角为钝角
    // 3: 夹角为平角，方向相反
    template<typename T>
    int angle_type_vector_vector(const Vector<T>& v1, const Vector<T>& v2){
        auto _d = dot(v1, v2);
        if(relation_vector_vector(v1, v2) == 0){ // 向量共线
            if(sgn(_d) > 0) return 0; // 同向
            return 3;
        }else{
            if(sgn(_d) > 0) return 1;
            return 2;
        }
    }

    // 两条直线的交点（要先判断两直线是否相交）
    template<typename T>
    Point<T> cross_point_line_line(const Line<T>& v1, const Line<T>& v2){
        auto a = v1.s, b = v1.t; // 直线 a - b
        auto c = v2.s, d = v2.t; // 直线 c - d
        double s1 = cross(b - a, c - a);
        double s2 = cross(b - a, d - a);
        return Point<T>(c.x * s2 - d.x * s1, c.y * s2 - d.y * s1) / (s2 - s1);
    }

    // 两个线段是否相交
    // 1: 相交，0: 不相交
    template<typename T>
    bool is_cross_segment_segment(const Segment<T>& v1, const Segment<T>& v2){
        auto a = v1.s, b = v1.t; // 线段 a - b
        auto c = v2.s, d = v2.t; // 线段 c - d
        double c1 = cross(b - a, c - a), c2 = cross(b - a, d - a);
        double d1 = cross(d - c, a - c), d2 = cross(d - c, b - c);
        return sgn(c1) * sgn(c2) < 0 && sgn(d1) * sgn(d2) < 0;
    }

    // 点与多边形关系
    // 0: 点在多边形外部
    // 1: 点在多边形内部
    // 2: 点在多边形边上
    // 3: 点在多边形顶点上
    template<typename T>
    int relation_point_polygon(const Point<T>& pt, const Polygon<T>& p){
        int n = p.size();
        for(int i = 0; i < n; i ++ ){
            if(p[i] == pt) return 3; // 是某一个点
        }
        for(int i = 0; i < n; i ++ ){
            Line<T> v(p[i], p[(i + 1) % n]);
            if(relation_point_segment(pt, v)) return 2; // 在某条边上
        }
        // 通过射线法计算点是否在多边形内部
        int num = 0;
        for(int i = 0; i < n; i ++ ){
            int j = (i + 1) % n;
            int c = sgn(cross(pt - p[j], p[i] - p[j]));
            int s1 = sgn(p[i].y - pt.y);
            int s2 = sgn(p[j].y - pt.y);
            if(c > 0 && s1 < 0 && s2 >= 0) num ++ ;
            if(c < 0 && s1 >= 0 && s2 < 0) num -- ;
        }
        return num;
    }

    // 多边形周长
    template<typename T>
    double peri_polygon(const Polygon<T>& p){
        double ans = 0;
        int n = p.size();
        for(int i = 0; i < n; i ++ ){
            ans += dist(p[i], p[(i + 1) % n]);
        }
        return ans;
    }

    // 多边形面积，逆时针遍历为正，顺时针遍历为负
    template<typename T>
    double area_polygon(const Polygon<T>& p){
        double area = 0;
        int n = p.size();
        for(int i = 0; i < n; i ++ )
            area += cross(p[i], p[(i + 1) % n]);
        return abs(area) / 2.0;
    }

    // 多边形的重心
    template<typename T>
    Point<T> center_polygon(const Polygon<T>& p){
        Point<T> ans(0, 0);
        int n = p.size();
        if(area_polygon(p) == 0) return ans;
        for(int i = 0; i < n; i ++ ){
            int j = (i + 1) % n;
            ans = ans + (p[i] + p[j]) * cross(p[i], p[j]);
        }
        return ans / area_polygon(p) / 6;
    }

    // 极角排序（Cross），点/向量。输入极点，默认为(0, 0)。逆时针排序
    template<typename T>
    void sort_polar_angle_cross(vector<Point<T>>& p, const Point<T>& O = Point<T>(0, 0)){
        sort(p.begin(), p.end(), [&](Point<T> A, Point<T> B){
            A = A - O, B = B - O;
            if(A.quadrant() != B.quadrant()){
                return A.quadrant() < B.quadrant();
            }
            auto sg = sgn(cross(A, B));
            if(sg == 0) return len(A) < len(B); // 共线取靠近的
            return sg > 0; 
        });
    }

    // 极角排序（atan2），点/向量
    template<typename T>
    void sort_polar_angle_atan2(vector<Point<T>>& p, const Point<T>& O = Point<T>(0, 0)){
        sort(p.begin(), p.end(), [&](const Point<T>& A, const Point<T>& B){
            return A.polar_angle(O) < B.polar_angle(O); 
        });
    }

    // 凸多边形：是指所有内角大小都在 [0, 180] 范围内的简单多边形
    // 凸包: 在平面上能包含所有给定点的最小凸多边形叫做凸包
    template<typename T>
    Polygon<T> convex_hull(vector<Point<T>> p){
        // Andrew 法
        // 先对所有点排序，求上下凸包 (查每个边相较于上一条边的拐弯方向)
        // 然后合并，最后得到的点为逆时针顺序
        Polygon<T> ch;
        if(p.size() <= 2){
            for(auto& x : p) ch.push_back(x);
            return ch;
        }
        int n = p.size();
        n = unique(p.begin(), p.end()) - p.begin(); // 去除重复的点
        ch.resize(2 * n);
        sort(p.begin(), p.end()); // operator<
        int tp = 0;
        // 求下凸包，若 p[i] 是右拐弯的，这个点不在凸包上，往回退
        for(int i = 0; i < n; i ++ ){
            while(tp > 1 && sgn(cross(ch[tp - 1] - ch[tp - 2], p[i] - ch[tp - 1])) <= 0)
                tp -- ;
            ch[tp ++ ] = p[i];
        }
        // 求上凸包
        for(int i = n - 1, j = tp; i >= 0; i -- ){
            while(tp > j && sgn(cross(ch[tp - 1] - ch[tp - 2], p[i] - ch[tp - 1])) <= 0)
                tp -- ;
            ch[tp ++ ] = p[i];
        }
        ch.resize(tp - 1);
        return ch;
    }

    // 点 p 与圆 C 的关系
    // 0: 点在圆内
    // 1: 点在圆上
    // 2: 点在圆外
    template<typename T>
    int relation_point_circle(const Point<T>& p, const Circle<T>& C){
        double d = dist(p, C.c); // 点到圆心距离
        if(sgn(d - C.r) < 0) return 0;  // 在圆内
        if(sgn(d - C.r) == 0) return 1; // 在圆上
        return 2;
    }

    // 直线 v 和圆 C 的关系
    // 0: 直线和圆相交
    // 1: 直线和圆相切
    // 2: 直线在圆外
    template<typename T>
    int relation_line_circle(const Line<T>& v, const Circle<T>& C){
        double d = dist_point_line(C.c, v); // 圆心到直线距离
        if(sgn(d - C.r) < 0) return 0;
        if(sgn(d - C.r) == 0) return 1; // 相切
        return 2;
    }

    // 线段 v 和圆 C 的关系（根据圆心到线段距离）
    // 0: 线段在圆内
    // 1: 线段和圆相切
    // 2: 线段在圆外
    template<typename T>
    int relation_segment_circle(const Segment<T>& v, const Circle<T>& C){
        double d = dist_point_segment(C.c, v); // 圆心到线段距离
        if(sgn(d - C.r) < 0) return 0;
        if(sgn(d - C.r) == 0) return 1; // 相切
        return 2;
    }

    // 求出直线与圆的交点 p1, p2
    template<typename T>
    int cross_point_line_circle(const Line<T>& v, const Circle<T>& C, Point<T>& p1, Point<T>& p2){
        if(relation_line_circle(v, C) == 2) return 0; // 无交点
        Point<T> q = proj_point_line(C.c, v); // 圆心到直线的投影
        double d = dist_point_line(C.c, v); // 圆心到直线距离
        double t = sqrt(C.r * C.r - d * d);
        if(sgn(t) == 0){
            p1 = p2 = q; // 说明相切，只有一个交点 
            return 1;
        }
        Point<T> n = unit_vector(v.t - v.s); // 单位向量
        p1 = q + n * t, p2 = q - n * t;
        return 2;
    }

    // 扇形面积，传入角度制
    template<typename T>
    double arc_area_circle(const Circle<T>& C, double deg){
        return C.area() * (deg / 360.0);
    }

    // 计算圆的面积
    template<typename T>
    double area_circle(const Circle<T>& C){ return C.area(); }

    // 三点确定一个外接圆
    template<typename T>
    Circle<double> get_circum_circle(const Point<T>& A, const Point<T>& B, const Point<T>& C){
        double Bx = B.x - A.x, By = B.y - A.y;
        double Cx = C.x - A.x, Cy = C.y - A.y;
        double D = 2.0 * (Bx * Cy - By * Cx);

        double x = (Cy * (Bx * Bx + By * By) - By * (Cx * Cx + Cy * Cy)) / D + A.x;
        double y = (Bx * (Cx * Cx + Cy * Cy) - Cx * (Bx * Bx + By * By)) / D + A.y;
        Point<T> O(x, y);
        return Circle(O, dist(A, O));
    }

    // 三点构成三角形的内切圆
    template<typename T>
    Circle<double> get_inside_circle(const Point<T>& A, const Point<T>& B, const Point<T>& C){
        double a = dist(B, C);
        double b = dist(A, C);
        double c = dist(A, B);
        Point<T> o = (A * a + B * b + C * c) / (a + b + c);
        return Circle(o, dist_point_line(o, Line<T>(A, B)));
    }
      
    // 旋转卡壳 求出最远点对，返回最远距离
    // 最远点对一定在凸包上，逆时针枚举边，对应最远点也在逆时针旋转，不会反向
    // p 为凸包，a、b为最远的两个点
    template<typename T>
    double farthest_dist_p2p(const Polygon<T>& p, Point<T>& a, Point<T>& b){
        double mx = 0;
        int n = p.size();
        for(int i = 0, j = 1; i < n; i ++ ){
            // 通过面积判断最远点
            while(abs(area_parallelogram(p[(i + 1) % n], p[i], p[(j + 1) % n])) > 
                abs(area_parallelogram(p[(i + 1) % n], p[i], p[j]))){
                j = (j + 1) % n;
            }
            double d1 = dist(p[i], p[j]);
            if(d1 > mx){
                mx = d1;
                a = p[i], b = p[j];
            }
            double d2 = dist(p[(i + 1) % n], p[j]);
            if(d2 > mx){
                mx = d2;
                a = p[(i + 1) % n], b = p[j];
            }
        }
        return mx;
    }

    template<typename T>
    T farthest_dist2_p2p(const Polygon<T>& p, Point<T>& a, Point<T>& b){
        T mx = 0;
        int n = p.size();
        for(int i = 0, j = 1; i < n; i ++ ){
            // 通过面积判断最远点
            while(abs(area_parallelogram(p[(i + 1) % n], p[i], p[(j + 1) % n])) > 
                abs(area_parallelogram(p[(i + 1) % n], p[i], p[j]))){
                j = (j + 1) % n;
            }
            double d1 = dist2(p[i], p[j]);
            if(d1 > mx){
                mx = d1;
                a = p[i], b = p[j];
            }
            double d2 = dist2(p[(i + 1) % n], p[j]);
            if(d2 > mx){
                mx = d2;
                a = p[(i + 1) % n], b = p[j];
            }
        }
        return mx;
    }

    // 旋转卡壳，只求最远距离
    template<typename T>
    double farthest_dist_p2p(const Polygon<T>& p){
        double mx = 0;
        int n = p.size();
        for(int i = 0, j = 1; i < n; i ++ ){
            // 通过面积判断最远点
            while(abs(area_parallelogram(p[(i + 1) % n], p[i], p[(j + 1) % n])) > 
                abs(area_parallelogram(p[(i + 1) % n], p[i], p[j]))){
                j = (j + 1) % n;
            }
            mx = max({mx, dist(p[i], p[j]), dist(p[(i + 1) % n], p[j])});
        }
        return mx;
    }

    // 旋转卡壳，只求最远距离平方
    template<typename T>
    T farthest_dist2_p2p(const Polygon<T>& p){
        T mx = 0;
        int n = p.size();
        for(int i = 0, j = 1; i < n; i ++ ){
            // 通过面积判断最远点
            while(abs(area_parallelogram(p[(i + 1) % n], p[i], p[(j + 1) % n])) > 
                abs(area_parallelogram(p[(i + 1) % n], p[i], p[j]))){
                j = (j + 1) % n;
            }
            mx = max({mx, dist2(p[i], p[j]), dist2(p[(i + 1) % n], p[j])});
        }
        return mx;
    }

    // 判断 b 和 c 的交点是否在 a 的右侧（用于求解半平面交）
    template<typename T> 
    inline bool on_right(const Line<T>& a, const Line<T>& b, const Line<T>& c){
        auto o = cross_point_line_line(b, c); // 求b和c的交点o
        return sgn(area_parallelogram(a.s, a.t, o)) < 0;
    }

    // 半平面交
    template<typename T>
    double half_plane_intersection(vector<Line<T>>& v){
        // 对向量进行极角排序
        sort(v.begin(), v.end(), [&](const Line<T>& a, const Line<T>& b){
            if(sgn(a.polar_angle() - b.polar_angle()) == 0){  // 角度相同
                return area_parallelogram(a.s, a.t, b.t) < 0; // 面积为负，更左 
            }
            return a.polar_angle() < b.polar_angle();
        }); 
        // 自定义去重
        v.erase(unique(v.begin(), v.end(), [&](const Line<T>& a, const Line<T>& b){
            return sgn(a.polar_angle() - b.polar_angle()) == 0;
        }), v.end()); // 角度相同的直线只考虑最靠左的一条,靠近左边的是有效的
        int n = v.size();
        deque<int> deq; // 双端队列，存储边的下标
        for(int i = 0; i < n; i ++ ){
            // 删除队尾没有贡献的线段
            while(deq.size() > 1 && on_right(v[i], v[deq[deq.size() - 2]], v[deq.back()])){
                deq.pop_back();
            }
            // 删除队头没有贡献的线段
            while(deq.size() > 1 && on_right(v[i], v[deq[0]], v[deq[1]])){
                deq.pop_front();
            }
            deq.push_back(i); // 如果可以构成轮廓，将当前直线加入队列
        }
        // 队头、队尾相互更新，还要确保队尾和队头都是有效的
        while(deq.size() > 1 && on_right(v[deq[0]], v[deq[deq.size() - 2]], v[deq.back()])){
            deq.pop_back();
        }
        while(deq.size() > 1 && on_right(v[deq.back()], v[deq[0]], v[deq[1]])){
            deq.pop_front();
        }
        deq.push_back(deq.front()); // 轮廓闭合
        Polygon<T> res; // 轮廓所有顶点，存到一个多边形中（凸包）
        for(int i = 0; i < deq.size() - 1; i ++ ){
            res.push_back(cross_point_line_line(v[deq[i]], v[deq[i + 1]]));
        }
        return res.area(); // 求半平面交的面积，即这个凸包的面积
    }

    // 1. 点与向量: Point(x, y) 为点，Vector(x, y) 为向量
    template<typename T>
    class Point {
    public:
        T x, y; 
        
        // 构造函数
        Point(T _x = 0, T _y = 0): x(_x), y(_y) {}

        // 向量长度
        double len() const { return sqrt(len2()); }

        // 向量长度的平方
        T len2() const { return (*this) * (*this); }

        // 点所在象限 0, 1, 2, 3，(0, 0) 算在第1象限
        // 获取象限 (0, 1, 2, 3)
        int quadrant() const { return sgn(y < 0) << 1 | sgn(x < 0) ^ sgn(y < 0); }

        // 点相较于 O 点的极角
        double polar_angle(const Point<T>& O = Point(0, 0)) const {
            // [0, pi / 2] 第一象限
            // [pi / 2, pi] 第二象限
            // [-pi, -pi / 2] 第三象限
            // [-pi / 2, 0] 第四象限
            return atan2(y - O.y, x - O.x); 
        }

        // 点 - 点 = 向量，向量 AB = B - A
        Point operator- (const Point& B) const { return Point(x - B.x, y - B.y); }

        // 点 + 点 = 点，点 + 向量 = 向量，向量 + 向量 = 向量
        Point operator+ (const Point& B) const { return Point(x + B.x, y + B.y); }

        // 向量 \times 向量（叉积）
        T operator^ (const Point<T>& B) const { return x * B.y - y * B.x; }

        // 向量 \cdot 向量（点积）
        T operator* (const Point<T>& B) const { return x * B.x + y * B.y; }

        // 点 \times 数 = 点，向量 \times 数 = 向量
        Point operator* (const double& b) const { return Point(x * b, y * b); }

        // 点 / 数 = 点，向量 /  数 = 向量
        Point operator/ (const double& b) const { return Point(x / b, y / b); }

        // 判断大小，小于大于，是否相等
        bool operator< (const Point& B) const { return x < B.x || (x == B.x && y < B.y); }
        bool operator> (const Point& B) const { return x > B.x || (x == B.x && y > B.y); }
        bool operator== (const Point& B) const { return !sgn(x - B.x) && !sgn(y - B.y); }
        bool operator!= (const Point& B) const { return sgn(x - B.x) || sgn(y - B.y); }
    };

    // 2. 直线与线段: Line 直线，Segment 线段
    template<typename T>
    class Line {
    public:
        Point<T> s, t; // 线上两点，s - t
        Line() {} // (0, 0) - (0, 0)
        Line(const Point<T>& p1, const Point<T>& p2): s(p1), t(p2) {}
        Line(double a, double b, double c){ // ax + by + c = 0
            if(sgn(a) == 0){
                s = Point<T>(0, -c / b);
                t = Point<T>(1, -c / b);
            }else if(sgn(b) == 0){
                s = Point<T>(-c / a, 0);
                t = Point<T>(-c / a, 1);
            }else{
                s = Point<T>(0, -c / b);
                t = Point<T>(1, (-c - a) / b);
            }
        }

        // 直线的极角，用于半平面交
        double polar_angle() const { return atan2(t.y - s.y, t.x - s.x); }

        // 计算斜率k，若平行于 y 轴，斜率不存在
        double k() const {
            if(sgn(t.x - s.x) == 0){
                throw runtime_error("Vertical line has undefined slope.");
            }
            return double(t.y - s.y) / (t.x - s.x);
        }

        // 计算截距b，若平行于 y 轴，截距不存在
        double b() const {
            if (sgn(t.x - s.x) == 0) { // 垂直线，斜率不存在
                throw runtime_error("Vertical line does not have a y-intercept.");
            }
            return s.y - k() * s.x;
        }
    };

    // 3. 多边形
    template<typename T>
    class Polygon: public vector<Point<T>> { // 继承自std::vector
    public:
        Polygon() {}
        Polygon(int n): vector<Point<T>>(n) {}

        // 多边形周长
        double peri() const {
            double ans = 0;
            int n = this->size();
            if(n < 2) return 0.0;
            for(int i = 0; i < n; i ++ ){
                ans += dist((*this)[i], (*this)[(i + 1) % n]);
            }
            return ans;
        }

        // 凸多边形面积
        double area() const {
            double ans = 0;
            int n = this->size();
            if(n < 3) return 0.0;
            for(int i = 0; i < n; i ++ ){ // 外面的面积抵消
                ans += cross((*this)[i], (*this)[(i + 1) % n]);
            }
            return abs(ans) / 2.0;
        }

        // 极角排序（Cross），输入极点，默认为(0, 0)。逆时针排序
        void sort_polar_angle_cross(const Point<T>& O = Point<T>(0, 0)){
            sort(this->begin(), this->end(), [&](Point<T> A, Point<T> B){
                A = A - O, B = B - O;
                if(A.quadrant() != B.quadrant()){
                    return A.quadrant() < B.quadrant();
                }
                auto sg = sgn(cross(A, B));
                if(sg == 0) return len(A) < len(B); // 共线取靠近的
                return sg > 0; 
            });
        }

        // 极角排序（atan2）
        void sort_polar_angle_atan2(const Point<T>& O = Point<T>(0, 0)){
            sort(this->begin(), this->end(), [&](const Point<T>& A, const Point<T>& B){
                if(sgn(cross(A, B)) == 0) return len(A) < len(B);
                return A.polar_angle(O) < B.polar_angle(O);
            });
        }
    };

    // 4. 圆
    template<typename T>
    class Circle{
    public:
        Point<T> c; // 圆心
        T r; // 半径
        Circle() {}
        Circle(Point<T> _c, T _r): c(_c), r(_r) {}
        Circle(T x, T y, T _r){ c = Point<T>(x, y); r = _r; }

        // 圆的周长
        double peri() const { return PI * 2 * r; }

        // 圆的面积
        double area() const { return PI * r * r; }

        // 扇形面积（角度制）
        double arc_area(double deg) const { return area() * (deg / 360.0); } 
    };
}

using namespace Geo;
using ll = long long;

void marisa(){
    int n, k; cin >> n >> k;
    vector<Point<ll>> p(n);
    for(int i = 0; i < n; i ++ ){
        cin >> p[i].x >> p[i].y;
    }
    sort_polar_angle_cross(p);
    for(const auto& [x, y] : p){
        cout << x << ' ' << y << "\n";
    }
    // double ans = 0;
    // for(int i = 0; i < n; i ++ ){
    //     int j = (i + k - 1) % n;
    //     ans = max(ans, angle(p[i], p[j]));
    // }
    // printf("%.10lf\n", ans);
}

int main(){
    ios;

    int T = 1; cin >> T;
    while(T -- ) marisa();

    return 0;
}