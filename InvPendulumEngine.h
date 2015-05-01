#ifndef INVPENDULUMENGINE_H
#define INVPENDULUMENGINE_H

#define M_PI 3.14159265
#define DEG_TO_RAD M_PI/180.0


class InvPendulumEngine
{
    public:
        InvPendulumEngine();
        ~InvPendulumEngine();
        InvPendulumEngine(const InvPendulumEngine& other);
        InvPendulumEngine& operator=(const InvPendulumEngine& other);

        void step();

        // getters and setters
        double Get_time_step() { return time_step; }
        void Set_time_step(double val) { time_step = val; }
        double Get_pen_len() { return pen_len; }
        void Set_pen_len(double val) { pen_len = val; }
        double Get_pen_mass() { return pen_mass; }
        void Set_pen_mass(double val) { pen_mass = val; }
        double Get_pen_angle() { return pen_angle/(DEG_TO_RAD); }
        void Set_pen_angle(double val) { pen_angle = val*(DEG_TO_RAD); }
		double Get_pen_angular_vel() { return pen_angular_vel; }
		void Set_pen_angular_vel(double val) { pen_angular_vel = val; }
        double Get_cart_mass() { return cart_mass; }
        void Set_cart_mass(double val) { cart_mass = val; }
        double Get_cart_pos() { return cart_pos; }
        void Set_cart_pos(double val) { cart_pos = val; }
        double Get_gravity() { return gravity; }
        void Set_gravity(double val) { gravity = val; }
        double Get_cart_vel() { return cart_vel; }
        void Set_cart_vel(double val) { cart_vel = val; }
        void Set_controller_fun( double (*controller) (double, double) ) { this->controller = controller; }

		enum IntegrationMethod {
			EULER,
			RK4,
		};

		IntegrationMethod GetIntegrationMethod() { return step_im; }
		void SetIntegrationMethod(IntegrationMethod im) { step_im = im; }

    private:
        double time_step;

        // the controller function will be called every ctrl_step_len step of simulation
        int ctrl_step_len;

        double pen_len;
        double pen_mass;
        double pen_angle;
		double pen_angular_vel;
        double cart_mass;
        double cart_pos;
		double cart_vel;

		double force;
		double nextForce;

        double gravity;

        // controller function pointer, returns servo position signal.
        double (*controller) (double cart_pos, double pen_angle);

		IntegrationMethod step_im;

		double sqr(double val) { return val*val; }

		void UpdatePhysicsEuler();
		void UpdatePhysicsRK4();
};

#endif // INVPENDULUMENGINE_H
