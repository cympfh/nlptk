# APRF -- Accuracy, Precision, Recall and F1 score

From the answer and the predict of a machine,
APRF calculates Acc, Prec, Rec and F1.
Prec, Rec and F1 are calculated for each class.
And the micro-average and macro-average of F1.

## Usage

```bash
./aprf <answer-file> <predict-file>
```

## File format

answer-file:

```
<label> ...
<label> ...
<label> ...
<label> ...
```

That is the format same as that of SVMlight and libsvm.
The format of predict-file is likewise.

