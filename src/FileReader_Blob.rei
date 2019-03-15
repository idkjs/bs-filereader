type t = FileReader__.blob;

include (module type of
  FileReader_BlobLike.Make({
    type nonrec t = t;
  }));

let asFile: t => option(t);

let make:
  (
    array(FileReader_BlobPart.t),
    ~type_: string=?,
    ~endings: string=?,
    unit
  ) =>
  t;