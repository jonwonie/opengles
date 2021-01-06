package pub.sweets.opengles;

import android.os.Bundle;
import android.view.MenuItem;
import android.view.Window;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;

import static androidx.appcompat.app.AppCompatDelegate.FEATURE_SUPPORT_ACTION_BAR;


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
public class RenderActivity extends AppCompatActivity {


    @Override
    public void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        getWindow().requestFeature(FEATURE_SUPPORT_ACTION_BAR);
        setContentView(R.layout.activity_triangle);
        if (getActionBar() != null)
            getActionBar().setDisplayHomeAsUpEnabled(true);
        if (getSupportActionBar() != null) {
            getSupportActionBar().setDisplayHomeAsUpEnabled(true);
        }

        setTitle(getIntent().getStringExtra("title"));

        int type = getIntent().getIntExtra("type", 0);
        ((ExGLSurfaceView) findViewById(R.id.surface)).setType(type);
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        if (item.getItemId() == android.R.id.home) {
            finish();
            return true;
        }
        return super.onOptionsItemSelected(item);
    }
}
