set number    " display line number
map <F4> : set nu!<BAR>set nonu?<CR>    " click F4 to on/off line number
set tabstop=4    " set tab width as 4; still it is a '\t'
" set expandtab    " define tab as 4 spaces: expand tab to spaces
" set shiftwidth=4    " define tab as 4 spaces: indents will have a width of 4local noexpandtab
set ic    " case insensitive in search
set wrap    " wrap if word too long
set showmatch    " Set matching mode: display matching brackets
set guifont=Inconsolata\ for\ Powerline\ 20    " Set gvim font and size
" set nowrap    " nowrap if word too long
" set cursorline    " highlight current line
" set cursorcolumn    " highlight current column
" set hlsearch    " String found by highlight
" set incsearch    " Show results instantly during search
" set autoindent    " Set auto indent
" set cindent    " Use automatic indentation of C/C++ language
" set smartindent    " Smart indentation
" set completeopt=longest,menu    " Smart completion
" set showcmd    " Display the command being entered in the status bar
" set mouse=nv
" set mouse-=a

" Enable folding
set foldmethod=indent
set foldlevel=99
nnoremap <space> za    " Enable folding with the spacebar

" Highlight area at the 120th character
set colorcolumn=120
highlight ColorColumn guibg=#202020

" Display tab
set listchars=tab:\|.
set list

" BadWhitespace
" highlight BadWhitespace ctermbg=red guibg=red    " Use the below highlight group when displaying bad whitespace is desired
" au BufRead,BufNewFile *.py,*.pyw match BadWhitespace /^\t\+/    " Display tabs at the beginning of a line in Python mode as bad
" au BufRead,BufNewFile *.py,*.pyw,*.c,*.h match BadWhitespace /\s\+$/    " Make trailing whitespace be flagged as bad

" Auto completion: {, (, <, [, ", '
" : inoremap { {}
" : inoremap ( ()
" : inoremap < <>
" : inoremap [ []
" : inoremap " ""
" : inoremap ' ''

" Makefile
autocmd FileType make set    " cancel expandtab setting: Makefile needs to distinguish between tab and space

" C
set tags=./tags,./TAGS,tags;~,TAGS;~    " moved to the function, type Ctrl+] to jump to the definition and then type Ctrl+t
autocmd FileType c set tabstop=4 | set expandtab | set shiftwidth=4

" Python
" au BufNewFile,BufRead *.py
"  \ set tabstop=4 |
"  \ set softtabstop=4 |
"  \ set shiftwidth=4 |
"  \ set textwidth=79 |
"  \ set expandtab |
"  \ set autoindent |
"  \ set fileformat=unix
" let python_highlight_all=1
" syntax on


" ======== Environment ========
" # lsb_release -a
" # vim --version | head -n2
" # apt install vim-gtk -y
" # apt install git -y

" # ctags --version; cscope --version
" # apt install exuberant-ctags cscope -y

" Install plugin management tool: Vundle
" # git clone https://github.com/VundleVim/Vundle.vim.git ~/.vim/bundle/Vundle.vim

" Vundle Plugins - airline
" # git clone https://github.com/powerline/fonts; cd fonts && ./install.sh; cd -

" Vundle Plugins - YouCompleteMe
" # apt install build-essential cmake python3-dev -y
" # cd ~/.vim/bundle; git clone https://github.com/Valloric/YouCompleteMe.git
" # cd ~/.vim/bundle/YouCompleteMe
" # git submodule update --init --recursive
" # ./install.py --clang-completer    " Compiling YCM with semantic support for C-family languages through libclang
" # ./install.py --clangd-completer    " Compiling YCM with semantic support for C-family languages through experimental clangd
" # python3 install.py    " Compiling YCM without semantic support for C-family languages


" ======== Start Vundle ========
set nocompatible    " required
filetype off    " required
set rtp+=~/.vim/bundle/Vundle.vim    " set the runtime path to include Vundle and initialize
call vundle#begin()    " alternatively, pass a path where Vundle should install plugins, call vundle#begin('~/some/path/here')


" ======== Write your plugins here ========
" let Vundle manage Vundle, required
Plugin 'VundleVim/Vundle.vim'

" Layouts
Plugin 'Yggdroot/indentLine'    " indent???????????????
Plugin 'ntpeters/vim-better-whitespace'    " ??????????????????

" Markdown
Plugin 'vim-pandoc/vim-pandoc-syntax'

" Misc tools
Plugin 'Valloric/YouCompleteMe'
let g:ycm_autoclose_preview_window_after_completion=1
map <leader>g  :YcmCompleter GoToDefinitionElseDeclaration<CR>

Plugin 'vim-airline/vim-airline'    " ??????????????????, ??????git??????
let g:airline_powerline_fonts = 1
set laststatus=2

Plugin 'tpope/vim-fugitive'    " ???vim?????????git??????

Plugin 'chazy/cscope_maps'    " ???cscope???????????????hotkey
" find: Query for a pattern  ??????????????????????????????statement, ?????? ctrl + \ + c|d|e|f|g|i|s|t ????????????
"  c: Find functions calling this function
"  d: Find functions called by this function
"  e: Find this egrep pattern
"  f: Find this file
"  g: Find this definition
"  i: Find files #including this file
"  s: Find this C symbol
"  t: Find this text string

Plugin 'wesleyche/SrcExpl'    " Source Explorer: ??????????????????function??????
Plugin 'vim-scripts/taglist.vim'    " Taglist: ?????????????????????symbols, ???????????????symbol???
Plugin 'scrooloose/nerdtree'    " NERD Tree: ??????????????????
Plugin 'wesleyche/Trinity'    " ??????SrcExpl, taglist, nerdtree??????
nmap <F6>  :TrinityToggleAll<CR>    " Open/Close SrcExpl , Taglist, Nerdtree
nmap <F7>  :TrinityToggleSourceExplorer<CR>    " Open/Close SrcExpl separately
nmap <F8>  :TrinityToggleTagList<CR>    " Open/Close Taglist separately
nmap <F9>  :TrinityToggleNERDTree<CR>    " Open/Close Nerdtree separately

Plugin 'majutsushi/tagbar'    " taglist??????
nmap <F10>  :TagbarToggle<CR>    " Open/Close Tagbar separately

" Plugin 'scrooloose/syntastic'
" set statusline+=%#warningmsg#
" set statusline+=%{SyntasticStatuslineFlag()}
" set statusline+=%*
" let g:syntastic_always_populate_loc_list = 1
" let g:syntastic_auto_loc_list = 1
" let g:syntastic_check_on_open = 1
" let g:syntastic_check_on_wq = 0
" let g:syntastic_python_checkers = ['pylint']
" let g:syntastic_python_pylint_args = '--disable=missing-docstring'

" Plugin 'nvie/vim-flake8'

" Plugin 'kien/ctrlp.vim'


" ======== Run vundle ========
" All of your Plugins must be added before the following line
call vundle#end()    " required
filetype plugin indent on    " required
" To ignore plugin indent changes, instead use:
" filetype plugin on
"
" Brief help
" :PluginList       - lists configured plugins
" :PluginInstall    - installs plugins; append `!` to update or just :PluginUpdate
" :PluginSearch foo - searches for foo; append `!` to refresh local cache
" :PluginClean      - confirms removal of unused plugins; append `!` to auto-approve removal
"
" see :h vundle for more details or wiki for FAQ
" Put your non-Plugin stuff after this line
