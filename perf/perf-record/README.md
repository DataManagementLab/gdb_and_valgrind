# Recording the profiling to a file
`perf record` can be used to sample events and the stack trace.
When no output path is specified, the sampled data is saved `perf.data`(if the file already exists, the old record is moved to `perf.data.old`).
The `-e` flag allows you to specify which events perf should record.
After the recording, you can either use `perf report` or `perf annotate` to analyze the profiling data.
`perf report`
