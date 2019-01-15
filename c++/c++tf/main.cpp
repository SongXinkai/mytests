#include <string>
#include <memory>
#include <boost/filesystem.hpp>
#include <glog/logging.h>
#include <gflags/gflags.h>

#include "tensorflow/core/public/session.h"
#include "tensorflow/core/protobuf/meta_graph.pb.h"

namespace fs = boost::filesystem;
namespace tf = tensorflow;

DEFINE_string(meta_graph_def, "meta_graph", "Path to meta_graph.");
DEFINE_string(checkpoint_path, "checkpoint", "Path to checkpoint.");
FLAGS_log_dir = "logs/";

int main(int argc, char* argv[]){
  google::ParseCommandLineFlags(&argc, &argv, true);
  google::InitGoogleLogging(argv[0]);

  std::unique_ptr<tensorflow::Session> sess;

  tf::MetaGraphDef meta_graph_def;
  tf::Status status = ReadBinaryProto(tf::Env::Default(), FLAGS_meta_graph_path, &meta_graph_def);
  LOG(INFO) << ;
  status = sess->Create(meta_graph_def);
  
  tf::Tensor checkpoint_path_tensor(tf::DT_STRING, tf::TensorShape());
  checkpoint_path_tensor.scalar<std::string>()() = FLAGS_checkpoint_path;
  status = sess->Run({}, 
                     {}, /* fetches_outputs is empty */
                     {},
                     nullptr
                    );
  return 0;
}
