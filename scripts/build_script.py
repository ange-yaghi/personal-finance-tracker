import os
import sys
import shutil

PARENT_DIR = '/../'
OUTPUT_DIR = '/workspace/build/'
PROJECT_DIR = '/project/'

def generate_target_path(app_name, architecture):
    full_dir = PARENT_DIR + OUTPUT_DIR + '/%s/%s/' % (architecture, app_name)
    return full_dir

def create_output_paths(app_name, architecture):
    full_dir = generate_target_path(app_name, architecture)
    
    try:
        shutil.rmtree(full_dir)
    except Exception:
        pass

    for i in range(10):
        try:
            os.makedirs(full_dir)
            break
        except Exception:
            print("Failed to create new output directory, trying again...")

def get_build_output_path(app_name, architecture, vs_output):
    build_output_path = PROJECT_DIR + ('/%s/' % app_name) + vs_output + '/'
    return build_output_path

def copy_executable(app_name, architecture, vs_output):
    full_dir = generate_target_path(app_name, architecture)
    build_output_path = get_build_output_path(app_name, architecture, vs_output)

    shutil.copy(build_output_path + '%s.exe' % app_name, full_dir)

def copy_required_folders(app_name, architecture):
    full_dir = generate_target_path(app_name, architecture)
    asset_dir = PARENT_DIR + '/assets/'

    try:
        shutil.copytree(asset_dir, full_dir + '/assets/')
    except FileNotFoundError:
        print('No assets found')

def copy_runtime_dependencies(app_name, architecture):
    full_dir = generate_target_path(app_name, architecture)
    runtime_dir = PARENT_DIR + '/dependencies/runtime/%s/' % architecture

    try:
        src_files = os.listdir(runtime_dir)
        for file_name in src_files:
            full_file_name = os.path.join(runtime_dir, file_name)
            if os.path.isfile(full_file_name):
                shutil.copy(full_file_name, full_dir)
    except FileNotFoundError:
        print('No runtime dependencies found')

if __name__ == '__main__':
    if len(sys.argv) != 4:
        raise Exception("Incorrect arguments; %d given, %d needed" % (len(sys.argv) - 1, 2))

    script_name = sys.argv[0]
    app_name = sys.argv[1]
    architecture = sys.argv[2]
    vs_output = sys.argv[3]

    PARENT_DIR = os.path.dirname(os.path.realpath(__file__)) + PARENT_DIR
    PROJECT_DIR = PARENT_DIR + PROJECT_DIR

    create_output_paths(app_name, architecture)
    copy_executable(app_name, architecture, vs_output)
    copy_required_folders(app_name, architecture)
    copy_runtime_dependencies(app_name, architecture)
