package pub.sweets.opengles;

import android.content.Context;
import android.graphics.PixelFormat;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 * <p>
 *
 * </p>
 * <pre>
 *            |ZZzzz
 *            |
 *            |
 *            |ZZzzz      /^\            |ZZzzz
 *            |          |~~~|           |
 *            |        |^^^^^^^|        / \
 *           /^\       |[]+    |       |~~~|
 *        |^^^^^^^|    |    +[]|       |   |
 *        |    +[]|/\/\/\/\^/\/\/\/\/|^^^^^^^|
 *        |+[]+   |~~~~~~~~~~~~~~~~~~|    +[]|
 *        |       |  []   /^\   []   |+[]+   |
 *        |   +[]+|  []  || ||  []   |   +[]+|
 *        |[]+    |      || ||       |[]+    |
 *        |_______|------------------|_______|
 * </pre>
 */
public class ExGLSurfaceView extends GLSurfaceView {

    static {
        System.loadLibrary("native-lib");
    }

    private ExRender exRender;
    private Integer type;

    public ExGLSurfaceView(Context context) {
        this(context, null);
    }

    public ExGLSurfaceView(Context context, AttributeSet attrs) {
        super(context, attrs);
        setEGLContextClientVersion(3);
        exRender = new ExRender();
        setEGLConfigChooser(8, 8, 8, 8, 16, 0);
        getHolder().setFormat(PixelFormat.RGBA_8888);
        setZOrderOnTop(true);
    }

    public void setType(Integer type) {
        if (type == null) {
            return;
        }
        this.type = type;
        setRenderer(new ExGLSurfaceRender(exRender, type));
        setRenderMode(RENDERMODE_CONTINUOUSLY);
    }

    @Override
    protected void onAttachedToWindow() {
        super.onAttachedToWindow();
        if (type != null) {
            exRender.init(type);
        }
    }

    @Override
    protected void onDetachedFromWindow() {
        exRender.release();
        super.onDetachedFromWindow();
    }

    static class ExGLSurfaceRender implements GLSurfaceView.Renderer {
        private ExRender exRender;
        private int type;

        public ExGLSurfaceRender(ExRender exRender, int type) {
            this.exRender = exRender;
            this.type = type;
        }

        @Override
        public void onSurfaceCreated(GL10 gl, EGLConfig config) {
            exRender.onSurfaceCreated();
            exRender.init(type);
        }

        @Override
        public void onSurfaceChanged(GL10 gl, int width, int height) {
            exRender.onSurfaceChanged(width, height);
        }

        @Override
        public void onDrawFrame(GL10 gl) {
            exRender.onDrawFrame();
        }
    }
}
