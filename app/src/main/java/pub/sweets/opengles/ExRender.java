package pub.sweets.opengles;

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
public class ExRender {

    public native void init(int type);

    public native void release();

    public native void onSurfaceCreated();

    public native void onSurfaceChanged(int width, int height);

    public native void onDrawFrame();
}
