package com.example.asm.finalproject;

import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import java.util.ArrayList;

/**
 * Created by mart_- on 19/06/2018.
 */

public class DeviceItemAdapter extends RecyclerView.Adapter<DeviceItemAdapter.MyViewHolder> {

    private ArrayList<DeviceItem> deviceItems = new ArrayList<>();
    private OnClickDeviceItemListener onClickDeviceItemListener;

    public DeviceItemAdapter(OnClickDeviceItemListener onClickDeviceItemListener) {
        this.onClickDeviceItemListener = onClickDeviceItemListener;
    }

    @Override
    public MyViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        LayoutInflater inflater = LayoutInflater.from(parent.getContext());
        View view = inflater.inflate(R.layout.device_item_cell, parent, false);
        return new MyViewHolder(view);
    }

    @Override
    public void onBindViewHolder(MyViewHolder holder, int position) {
        final DeviceItem deviceItem = deviceItems.get(position);
        holder.name.setText(deviceItem.getName());
        holder.itemView.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                onClickDeviceItemListener.OnClickDeviceItem(deviceItem);
            }
        });
    }

    @Override
    public int getItemCount() {
        return deviceItems.size();
    }

    public void add(DeviceItem deviceItem) {
        deviceItems.add(deviceItem);
        notifyDataSetChanged();
    }

    public class MyViewHolder extends RecyclerView.ViewHolder {
        private final TextView name;

        public MyViewHolder(final View itemView) {
            super(itemView);

            name = itemView.findViewById(R.id.name);
        }
    }
}
