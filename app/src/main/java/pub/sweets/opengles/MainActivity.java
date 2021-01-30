package pub.sweets.opengles;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.DiffUtil;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.ListAdapter;
import androidx.recyclerview.widget.RecyclerView;

import android.content.Intent;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.media.AudioRecord;
import android.os.Bundle;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import java.util.Arrays;
import java.util.Objects;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.ThreadPoolExecutor;
import java.util.concurrent.locks.AbstractQueuedSynchronizer;
import java.util.concurrent.locks.ReentrantLock;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        RecyclerView rv = findViewById(R.id.rv);
        ExListAdapter adapter = new ExListAdapter();
        adapter.submitList(Arrays.asList("Triangle"));
        rv.setAdapter(adapter);
        rv.setLayoutManager(new LinearLayoutManager(this));
        rv.addItemDecoration(new RecyclerView.ItemDecoration() {
            final Paint paint;

            {
                paint = new Paint(Paint.ANTI_ALIAS_FLAG);
                paint.setColor(Color.parseColor("#EFEFEF"));
                paint.setStrokeWidth(getResources().getDisplayMetrics().density);
            }

            @Override
            public void onDrawOver(@NonNull Canvas c, @NonNull RecyclerView parent, @NonNull RecyclerView.State state) {
                int n = parent.getChildCount();
                for (int i = 0; i < n; ++i) {
                    View child = parent.getChildAt(i);
                    c.drawLine(child.getLeft(), child.getBottom(), child.getRight(), child.getBottom(), paint);
                }
            }
        });
        ReentrantLock lock = new ReentrantLock();
        lock.lock();
    }


    static class ExListAdapter extends ListAdapter<String, ExListAdapter.ItemViewHolder> {
        protected ExListAdapter() {
            super(new DiffUtil.ItemCallback<String>() {
                @Override
                public boolean areItemsTheSame(@NonNull String oldItem, @NonNull String newItem) {
                    return Objects.equals(oldItem, newItem);
                }

                @Override
                public boolean areContentsTheSame(@NonNull String oldItem, @NonNull String newItem) {
                    return Objects.equals(oldItem, newItem);
                }
            });
        }

        @NonNull
        @Override
        public ExListAdapter.ItemViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
            TextView textView = new TextView(parent.getContext());
            final float density = parent.getContext().getResources().getDisplayMetrics().density;
            final int pad = (int) (density * 12 + 0.5);
            textView.setPadding(pad, 0, pad, 0);
            textView.setLayoutParams(new RecyclerView.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, (int) (density * 50 + 0.5)));
            textView.setGravity(Gravity.START | Gravity.CENTER);
            return new ItemViewHolder(textView);
        }

        @Override
        public void onBindViewHolder(@NonNull ExListAdapter.ItemViewHolder holder, int position) {
            holder.textView.setText(getItem(position));
        }

        class ItemViewHolder extends RecyclerView.ViewHolder {

            private TextView textView;

            public ItemViewHolder(@NonNull View itemView) {
                super(itemView);
                textView = (TextView) itemView;
                itemView.setOnClickListener(new View.OnClickListener() {
                    @Override
                    public void onClick(View v) {
                        Intent i = new Intent(v.getContext(), RenderActivity.class);
                        i.putExtra("type", getAdapterPosition());
                        i.putExtra("title", getItem(getAdapterPosition()));
                        v.getContext().startActivity(i);
                    }
                });
            }

        }
    }


}