# Recording the profiling to a file
`perf record` can be used to store the profiling data of run into a file.
When no output path is specified, the data is saved `perf.data`(if the file already exists, the old record is moved to `perf.data.old`).
The `-e` flag allows you to specify which events perf should record.
After the recording, you can either use `perf report` or `perf annotate` to analyze the profiling data.
`perf report`
